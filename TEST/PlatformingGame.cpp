#include "JDM.h"

JCLASS PlatformGames : JPUBLIC JWINDOW {
JPRIVATE:

    JSTRUCT Entity { JFLOAT X, Y, NX, NY, VX, VY, Accelaration; };
    JWSTR LevelMap;
    JINT LevelWidth;
    JINT LevelHeight;
    JINT TileWidth = 12;
    JINT TileHeight = 12;
    JINT TileVisibilityX;
    JINT TileVisibilityY;

    JFLOAT Gravity = 50.f;
    JFLOAT CameraX = 0.f;
    JFLOAT CameraY = 0.f;
    Entity Player = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};

JPUBLIC:
    PlatformGames() : JWINDOW("Basic Platform Game", 200, 120, 5, 5) { }
    JBOOL onUserCreate() {
        LevelWidth = 100;
        LevelHeight = 10;

        LevelMap += L"                                                                                                    ";
        LevelMap += L"                                                                                                    ";
        LevelMap += L"                                                                                                    ";
        LevelMap += L"                                                                                                    ";
        LevelMap += L"                                                                                                    ";
        LevelMap += L"                                                                                                    ";
        LevelMap += L"                                                                                                    ";
        LevelMap += L"             #                                                                                      ";
        LevelMap += L"            ###                                                                                     ";
        LevelMap += L"####################################################################################################";

        TileVisibilityX = GetWidth() / TileWidth;
        TileVisibilityY = GetHeight() / TileHeight;
        JRETURN JTRUE;
    }

    JWCHAR GetTile(JINT x, JINT y) {
        JIF (x >= 0 && x < LevelWidth && y >= 0 && y < LevelHeight)
                JRETURN LevelMap[y * LevelWidth + x];
        JELSE JRETURN JSTATICC<JWCHAR>(BLANK);
    }
    JVOID SetTile(JINT x, JINT y, JWCHAR Tile) {
        JIF (x >= 0 && x < LevelWidth && y >= 0 && y < LevelHeight)
            LevelMap[y * LevelWidth + x] = Tile;
    }

    JVOID CheckCollision(Entity &entity) {
        JIF(GetTile(entity.NX + ((entity.VX <= 0) ? 0.0f : 1.f), entity.Y + 0.f) != BLANK
         || GetTile(entity.NX + ((entity.VX <= 0) ? 0.0f : 1.f), entity.Y + 0.9f) != BLANK) {
            entity.NX = (JINT)entity.NX + ((entity.VX <= 0) ? 1 : 0);
            entity.VX = 0;
        }
        JIF(GetTile(entity.NX + 0.f, entity.NY + ((entity.VY <= 0) ? 0.f : 1.f)) != BLANK
         || GetTile(entity.NX + 0.9f, entity.NY + ((entity.VY <= 0) ? 0.f : 1.f)) != BLANK) {
            entity.NY = (JINT)entity.NY + ((entity.VY <= 0) ? 1 : 0);
            entity.VY = 0;
        }
        entity.X = entity.NX;
        entity.Y = entity.NY;
    }

    JVOID ApplyJump(Entity &entity) {
        entity.Accelaration = 0.f;
        entity.VY = -(Gravity / 8);
    }

    JVOID ApplyGravity(Entity &entity) {
        entity.Accelaration += Gravity * ElapseTime;
        JIF (entity.Accelaration >= Gravity / 2) entity.Accelaration = Gravity / 2;
        entity.VY += entity.Accelaration * ElapseTime;
        JIF (entity.VY >=  20.f) entity.VY = 20.f;
        entity.NY = entity.Y + entity.VY * ElapseTime;
    }

    JVOID ApplyMaxVel(Entity &entity) {
        JIF (entity.VX > 10.f) entity.VX = 10.f;
        JIF (entity.VX < -10.f) entity.VX = -10.f;
        JIF (entity.VY > 20.f) entity.VY = 20.f;
        JIF (entity.VY < -20.f) entity.VY = -20.f;
    }

    JBOOL onUserUpdate() {
        Clear(BLANK, BG_CYAN);

        Player.VX = 0;
        JIF (keyboard.Keys[Keys::J_AKEY].isHeld) Player.VX = -6.f;
        JIF (keyboard.Keys[Keys::J_DKEY].isHeld) Player.VX = 6.f;
        JIF (keyboard.Keys[Keys::J_JKEY].isPressed && Player.VY == 0) ApplyJump(Player);
        Player.NX = Player.X + Player.VX * ElapseTime;

        CheckCollision(Player);
        ApplyGravity(Player);
        CheckCollision(Player);

        CameraX = Player.X;
        CameraY = Player.Y;
        JFLOAT OffsetX = CameraX - (JFLOAT)TileVisibilityX / 2.0f;
        JFLOAT OffsetY = CameraY - (JFLOAT)TileVisibilityY / 2.0f;
        JIF(OffsetX < 0) OffsetX = 0;
        JIF(OffsetY < 0) OffsetY = 0;
        JIF(OffsetX > LevelWidth - TileVisibilityX) OffsetX = LevelWidth - TileVisibilityX;
        JIF(OffsetY > LevelHeight - TileVisibilityY) OffsetY = LevelHeight - TileVisibilityY;

        JFLOAT TileOffsetX = (OffsetX - (JINT)OffsetX) * TileWidth;
        JFLOAT TileOffsetY = (OffsetY - (JINT)OffsetY) * TileHeight;
        JFOR(JINT x = -2; x < TileVisibilityX + 2; x++)
            JFOR(JINT y = -2; y < TileVisibilityY + 2; y++) {
                JWCHAR TileID = GetTile(x + OffsetX, y + OffsetY);
                JSWITCH (TileID) {
                    JCASE L'#' : DrawBox({TileWidth, TileHeight, x * TileWidth - TileOffsetX, y * TileHeight - TileOffsetY}, PIXEL_SOLID, FG_DARK_RED, JTRUE); JBREAK;
                    JDEFAULT:  JBREAK;
                }
            }

        DrawBox({TileWidth, TileHeight, (Player.X - OffsetX) * TileWidth, (Player.Y - OffsetY) * TileHeight}, PIXEL_SOLID, FG_DARK_BLUE, JTRUE);
        JRETURN JTRUE;
    }
};

JINT main()
{
    JMS<PlatformGames>()->Start();
    JRETURN JFALSE;
}
