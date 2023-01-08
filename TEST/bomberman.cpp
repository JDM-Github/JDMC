#include "JDM.hpp"


JCLASS BomberMan : JPUBLIC JWINDOW {
JPRIVATE:

    JSTRUCT Entity{
        JINT SpriteIndex = 0;
        JFLOAT X = 1.f, Y = 1.f;
        JINT Speed = 6;
        JCHAR DirectionX = 'N';
        JCHAR DirectionY = 'N';
        JINT targetX = 1;
        JINT targetY = 1;
        JBOOL Moving = JFALSE;
    };

    JSTRUCT BombStruct {
        JFLOAT CBombTick = 3.f;
        JFLOAT BombTick = 0.f;
        JINT X = 0, Y = 0;
        JINT SpriteIndex = 0;
    };

    JBOOL isExploding = JFALSE;
    JINT ExplosionX = 0;
    JINT ExplosionY = 0;
    JINT ExplosionIndex = 0;
    JFLOAT ExplosionTick = 0.f;
    JCFLOAT CExplosionTick = 0.8f;

    JWSTR Map;
    JWSTR BombSprite[3];
    JWSTR BomberManSprite[12];

    JWSTR ExplosionMid[3];
    JWSTR ExplosionLeft[3];
    JWSTR ExplosionRight[3];
    JWSTR ExplosionXStem[3];
    JWSTR ExplosionUp[3];
    JWSTR ExplosionDown[3];
    JWSTR ExplosionYStem[3];

    JWSTR TileExplosion[3];

    JWSTR Tile0;
    JWSTR TileB;

    JINT Width = 20;
    JINT Height = 20;
    JINT MapWidth = 51;
    JINT MapHeight = 31;
    JINT TileVisX = 0;
    JINT TileVisY = 0;

    Entity Player{};
    BombStruct Bomb{};

    JINT FirePower = 1;

JPUBLIC:
    BomberMan() : JWINDOW("BomberMan", JSWMAX, JSHMAX, 3, 3) { }
    JBOOL onUserCreate() {

        GetSpriteString(BombSprite[0], "BombermanSprite/bomb/bomb1.sprt");
        GetSpriteString(BombSprite[1], "BombermanSprite/bomb/bomb2.sprt");
        GetSpriteString(BombSprite[2], "BombermanSprite/bomb/bomb3.sprt");

        GetSpriteString(BomberManSprite[0], "BombermanSprite/bomberman/bm1.sprt");
        GetSpriteString(BomberManSprite[1], "BombermanSprite/bomberman/bm2.sprt");
        GetSpriteString(BomberManSprite[2], "BombermanSprite/bomberman/bm3.sprt");
        GetSpriteString(BomberManSprite[3], "BombermanSprite/bomberman/bm4.sprt");
        GetSpriteString(BomberManSprite[4], "BombermanSprite/bomberman/bm5.sprt");
        GetSpriteString(BomberManSprite[5], "BombermanSprite/bomberman/bm6.sprt");
        GetSpriteString(BomberManSprite[6], "BombermanSprite/bomberman/bm7.sprt");
        GetSpriteString(BomberManSprite[7], "BombermanSprite/bomberman/bm8.sprt");
        GetSpriteString(BomberManSprite[8], "BombermanSprite/bomberman/bm9.sprt");
        GetSpriteString(BomberManSprite[9], "BombermanSprite/bomberman/bm10.sprt");
        GetSpriteString(BomberManSprite[10], "BombermanSprite/bomberman/bm11.sprt");
        GetSpriteString(BomberManSprite[11], "BombermanSprite/bomberman/bm12.sprt");

        GetSpriteString(ExplosionMid[0], "BombermanSprite/Explosion/midExp1.sprt");
        GetSpriteString(ExplosionMid[1], "BombermanSprite/Explosion/midExp2.sprt");
        GetSpriteString(ExplosionMid[2], "BombermanSprite/Explosion/midExp3.sprt");

        GetSpriteString(ExplosionXStem[0], "BombermanSprite/Explosion/stemXExp1.sprt");
        GetSpriteString(ExplosionXStem[1], "BombermanSprite/Explosion/stemXExp2.sprt");
        GetSpriteString(ExplosionXStem[2], "BombermanSprite/Explosion/stemXExp3.sprt");

        GetSpriteString(ExplosionYStem[0], "BombermanSprite/Explosion/stemYExp1.sprt");
        GetSpriteString(ExplosionYStem[1], "BombermanSprite/Explosion/stemYExp2.sprt");
        GetSpriteString(ExplosionYStem[2], "BombermanSprite/Explosion/stemYExp3.sprt");

        GetSpriteString(ExplosionLeft[0], "BombermanSprite/Explosion/leftExp1.sprt");
        GetSpriteString(ExplosionLeft[1], "BombermanSprite/Explosion/leftExp2.sprt");
        GetSpriteString(ExplosionLeft[2], "BombermanSprite/Explosion/leftExp3.sprt");

        GetSpriteString(ExplosionRight[0], "BombermanSprite/Explosion/rightExp1.sprt");
        GetSpriteString(ExplosionRight[1], "BombermanSprite/Explosion/rightExp2.sprt");
        GetSpriteString(ExplosionRight[2], "BombermanSprite/Explosion/rightExp3.sprt");

        GetSpriteString(ExplosionUp[0], "BombermanSprite/Explosion/upExp1.sprt");
        GetSpriteString(ExplosionUp[1], "BombermanSprite/Explosion/upExp2.sprt");
        GetSpriteString(ExplosionUp[2], "BombermanSprite/Explosion/upExp3.sprt");

        GetSpriteString(ExplosionDown[0], "BombermanSprite/Explosion/downExp1.sprt");
        GetSpriteString(ExplosionDown[1], "BombermanSprite/Explosion/downExp2.sprt");
        GetSpriteString(ExplosionDown[2], "BombermanSprite/Explosion/downExp3.sprt");

        GetSpriteString(TileExplosion[0], "BombermanSprite/tileExp1.sprt");
        GetSpriteString(TileExplosion[1], "BombermanSprite/tileExp2.sprt");
        GetSpriteString(TileExplosion[2], "BombermanSprite/tileExp3.sprt");


        GetSpriteString(Tile0, "BombermanSprite/0tile.sprt");
        GetSpriteString(TileB, "BombermanSprite/Btile.sprt");
        TileVisX = GetWidth() / Width;
        TileVisY = GetHeight() / Height;

        CreateMap();
        JRETURN JTRUE;
    }

    JVOID CreateMap() {
        Map.clear();
        JFOR (JINT y = 0; y < MapHeight; y++) {
            JFOR (JINT x = 0; x < MapWidth; x++) {
                JIF (y == 0 || x == 0 || y == MapHeight - 1 || x == MapWidth - 1) Map += L'U';
                JELSE JIF (y % 2 == 0 && x % 2 == 0) Map += L'U';
                JELSE JIF((Random() % 2) == 0) {
                    JIF((x == 1 && y == 1) || (x == 1 && y == 2) || (x == 2 && y == 1)) Map += L' ';
                    JELSE Map += L'B';
                }
                JELSE Map += L' ';
            }
        }
    }

    JWCHAR GetTile(JINT x, JINT y) {
        JIF (x >= 0 && x < MapWidth && y >= 0 && y < MapHeight)
                JRETURN Map[y * MapWidth + x];
        JELSE JRETURN JSTATICC<JWCHAR>(BLANK);
    }
    JVOID SetTile(JINT x, JINT y, JWCHAR Tile) {
        JIF (x >= 0 && x < MapWidth && y >= 0 && y < MapHeight)
            Map[y * MapWidth + x] = Tile;
    }

    JVOID MoveAnimation(Entity &entity) {
        JIF (entity.DirectionX != 'N') {
            entity.X += (entity.DirectionX == 'A') ? -entity.Speed * ElapseTime : entity.Speed * ElapseTime;
            JIF ((entity.DirectionX == 'A') ? (entity.X < entity.targetX) : (entity.X > entity.targetX)) {
                entity.SpriteIndex = (entity.DirectionX == 'A') ? 6 : 9;
                entity.X = entity.targetX;
                entity.DirectionX = 'N';
                entity.Moving = JFALSE;
            }
            JELSE JIF ((entity.DirectionX == 'A') ? (entity.X < (entity.targetX + 0.30f)) : (entity.X > (entity.targetX - 0.30f)))
                entity.SpriteIndex = (entity.DirectionX == 'A') ? 7 : 10;
            JELSE JIF ((entity.DirectionX == 'A') ? (entity.X < (entity.targetX + 0.65f)) : (entity.X> (entity.targetX- 0.65f)))
                entity.SpriteIndex = (entity.DirectionX == 'A') ? 6 : 9;
            JELSE JIF ((entity.DirectionX == 'A') ? (entity.X < (entity.targetX + 1.f)) : (entity.X > (entity.targetX - 1.f)))
                entity.SpriteIndex = (entity.DirectionX == 'A') ? 8 : 11;
        }
        JELSE JIF (entity.DirectionY != 'N') {
            entity.Y += (entity.DirectionY == 'W') ? -entity.Speed * ElapseTime : entity.Speed * ElapseTime;
            JIF ((entity.DirectionY == 'W') ? (entity.Y < entity.targetY) : (entity.Y > entity.targetY)) {
                entity.SpriteIndex = (entity.DirectionY == 'W') ? 3 : 0;
                entity.Y = entity.targetY;
                entity.DirectionY = 'N';
                entity.Moving = JFALSE;
                JRETURN;
            }
            JELSE JIF ((entity.DirectionY == 'W') ? (entity.Y < (entity.targetY + 0.30f)) : (entity.Y > (entity.targetY - 0.30f)))
                entity.SpriteIndex = (entity.DirectionY == 'W') ? 4 : 1;
            JELSE JIF ((entity.DirectionY == 'W') ? (entity.Y < (entity.targetY + 0.65f)) : (entity.Y> (entity.targetY - 0.65f)))
                entity.SpriteIndex = (entity.DirectionY == 'W') ? 3 : 0;
            JELSE JIF ((entity.DirectionY == 'W') ? (entity.Y < (entity.targetY + 1.f)) : (entity.Y > (entity.targetY - 1.f)))
                entity.SpriteIndex = (entity.DirectionY == 'W') ? 5 : 2;
        }
    }

    JBOOL canMove(JINT x, JINT y) {
        JWCHAR Item = GetTile(x, y);
        JIF(Bomb.BombTick > 0 && x == Bomb.X && y == Bomb.Y) JRETURN JFALSE;
        JRETURN (Item != L'U' && Item != L'B');
    }
    JVOID MoveEntity(JINT x, JINT y, JCHAR DX, JCHAR DY, JINT Index) {
        Player.SpriteIndex = Index;
        JIF (canMove(x, y)) {
            Player.Moving = JTRUE;
            Player.DirectionX = DX;
            Player.DirectionY = DY;
            Player.targetX = x;
            Player.targetY = y;
        }
    }

    JVOID SetExplode(JINT x, JINT y, JINT i) {
        JSWITCH (i) {
            JCASE 0 : SetTile(x, y, L'2'); JBREAK;
            JCASE 1 : SetTile(x, y, L'3'); JBREAK;
            JCASE 2 : SetTile(x, y, L' '); JBREAK;
        }
    }
    JBOOL onUserUpdate() {
        Clear(BLANK, BG_DARK_GREEN);

        JIF (keyboard.Keys[Keys::J_BKEY].isPressed && Bomb.BombTick <= 0) {
            Bomb.BombTick = Bomb.CBombTick;
            Bomb.X = (Player.DirectionX == 'A') ? std::floor(Player.X) : std::ceil(Player.X);
            Bomb.Y = (Player.DirectionY == 'W') ? std::floor(Player.Y) : std::ceil(Player.Y);
        }
        JIF (!Player.Moving) {
            JIF(keyboard.Keys[Keys::J_WKEY].isHeld) MoveEntity(Player.targetX, Player.targetY - 1, 'N', 'W', 3);
            JELSE JIF (keyboard.Keys[Keys::J_SKEY].isHeld) MoveEntity(Player.targetX, Player.targetY + 1, 'N', 'S', 0);
            JELSE JIF (keyboard.Keys[Keys::J_AKEY].isHeld) MoveEntity(Player.targetX - 1, Player.targetY, 'A', 'N', 6);
            JELSE JIF (keyboard.Keys[Keys::J_DKEY].isHeld) MoveEntity(Player.targetX + 1, Player.targetY, 'D', 'N', 9);
        }
        JELSE MoveAnimation(Player);

        JFLOAT OffsetX = Player.X - JSTATICC<JFLOAT>(TileVisX) / 2.f + 0.5f;
        JFLOAT OffsetY = Player.Y - JSTATICC<JFLOAT>(TileVisY) / 2.f + 0.5f;
        JIF(OffsetX < 0) OffsetX = 0;
        JIF(OffsetY < 0) OffsetY = 0;
        JIF(OffsetX > MapWidth - TileVisX) OffsetX = MapWidth - TileVisX;
        JIF(OffsetY > MapHeight - TileVisY) OffsetY = MapHeight - TileVisY;

        JFLOAT TileOffsetX = (OffsetX - JSTATICC<JINT>(OffsetX)) * Width;
        JFLOAT TileOffsetY = (OffsetY - JSTATICC<JINT>(OffsetY)) * Height;

        JFOR(JINT y = -2; y < TileVisY + 2; y++) {
            JFOR(JINT x = -2; x < TileVisX + 2; x++) {
                JWCHAR Item = GetTile(OffsetX + x, OffsetY + y);
                JSWITCH (Item) {
                JCASE L'U' : DrawCString({x * Width - TileOffsetX, y * Height - TileOffsetY}, Tile0, JTRUE); JBREAK;
                JCASE L'B' : DrawCString({x * Width - TileOffsetX, y * Height - TileOffsetY}, TileB, JTRUE); JBREAK;
                JCASE L'1' : DrawCString({x * Width - TileOffsetX, y * Height - TileOffsetY}, TileExplosion[0], JTRUE); JBREAK;
                JCASE L'2' : DrawCString({x * Width - TileOffsetX, y * Height - TileOffsetY}, TileExplosion[1], JTRUE); JBREAK;
                JCASE L'3' : DrawCString({x * Width - TileOffsetX, y * Height - TileOffsetY}, TileExplosion[2], JTRUE); JBREAK;
                }
            }
        }
        JIF (Bomb.BombTick > 0) {
            Bomb.BombTick -= ElapseTime;
            JIF (Bomb.BombTick <= 0) {
                ExplosionX = Bomb.X;
                ExplosionY = Bomb.Y;
                ExplosionTick = CExplosionTick;
                Bomb.SpriteIndex = 0;
            }
            JELSE JIF (Bomb.BombTick - JSTATICC<JINT>(Bomb.BombTick) <= 0.15f) Bomb.SpriteIndex = 0;
            JELSE JIF (Bomb.BombTick - JSTATICC<JINT>(Bomb.BombTick) <= 0.35f)  Bomb.SpriteIndex = 2;
            JELSE JIF (Bomb.BombTick - JSTATICC<JINT>(Bomb.BombTick) <= 0.45f) Bomb.SpriteIndex = 1;
            JELSE JIF (Bomb.BombTick - JSTATICC<JINT>(Bomb.BombTick) <= 0.65f) Bomb.SpriteIndex = 0;
            JELSE JIF (Bomb.BombTick - JSTATICC<JINT>(Bomb.BombTick) <= 0.75f)  Bomb.SpriteIndex = 2;
            JELSE JIF (Bomb.BombTick - JSTATICC<JINT>(Bomb.BombTick) <= 0.95f) Bomb.SpriteIndex = 1;
            DrawCString({(Bomb.X - OffsetX) * Width, (Bomb.Y - OffsetY) * Height}, BombSprite[Bomb.SpriteIndex], JTRUE);
        }
        JIF (ExplosionTick > 0) {
            ExplosionTick -= ElapseTime;
            JIF (ExplosionTick <= 0) {
                ExplosionIndex = 0;
            }
            JELSE JIF (ExplosionTick <= 0.25f)  ExplosionIndex = 0;
            JELSE JIF (ExplosionTick <= 0.45f) ExplosionIndex = 1;
            JELSE JIF (ExplosionTick <= 0.65f) ExplosionIndex = 2;
            DrawCString({(ExplosionX - OffsetX) * Width, (ExplosionY - OffsetY) * Height}, ExplosionMid[ExplosionIndex], JTRUE);

            JFOR(JINT i = 1; i < FirePower + 1; i++) {
                JWCHAR Item = GetTile(ExplosionX, ExplosionY + i);
                JIF (Item == L' ')
                DrawCString({(ExplosionX - OffsetX) * Width, ((ExplosionY + i) - OffsetY) * Height},
                    (i + 1 >= FirePower + 1) ? ExplosionDown[ExplosionIndex] : ExplosionYStem[ExplosionIndex], JTRUE);
                JELSE JIF (Item != L'U') {
                    SetExplode(ExplosionX, ExplosionY + i, ExplosionIndex);
                    JBREAK;
                }
                JELSE JBREAK;
            }
            JFOR(JINT i = 1; i < FirePower + 1; i++) {
                JWCHAR Item = GetTile(ExplosionX, ExplosionY - i);
                JIF (Item == L' ')
                DrawCString({(ExplosionX - OffsetX) * Width, ((ExplosionY - i) - OffsetY) * Height},
                    (i + 1 >= FirePower + 1) ? ExplosionUp[ExplosionIndex] : ExplosionYStem[ExplosionIndex], JTRUE);
                JELSE JIF (Item != L'U') {
                    SetExplode(ExplosionX, ExplosionY - i, ExplosionIndex);
                    JBREAK;
                }
                JELSE JBREAK;
            }
            JFOR(JINT i = 1; i < FirePower + 1; i++) {
                JWCHAR Item = GetTile(ExplosionX - i, ExplosionY);
                JIF (Item == L' ')
                DrawCString({((ExplosionX - i) - OffsetX) * Width, (ExplosionY - OffsetY) * Height},
                    (i + 1 >= FirePower + 1) ? ExplosionLeft[ExplosionIndex] : ExplosionXStem[ExplosionIndex], JTRUE);
                JELSE JIF (Item != L'U') {
                    SetExplode(ExplosionX - i, ExplosionY, ExplosionIndex);
                    JBREAK;
                }
                JELSE JBREAK;
            }
            JFOR(JINT i = 1; i < FirePower + 1; i++) {
                JWCHAR Item = GetTile(ExplosionX + i, ExplosionY);
                JIF (Item == L' ')
                DrawCString({((ExplosionX + i) - OffsetX) * Width, (ExplosionY - OffsetY) * Height},
                    (i + 1 >= FirePower + 1) ? ExplosionRight[ExplosionIndex] : ExplosionXStem[ExplosionIndex], JTRUE);
                JELSE JIF (Item != L'U') {
                    SetExplode(ExplosionX + i, ExplosionY, ExplosionIndex);
                    JBREAK;
                }
                JELSE JBREAK;
            }
        }
        DrawCString({(Player.X - OffsetX) * Width, (Player.Y - OffsetY) * Height}, BomberManSprite[Player.SpriteIndex], JTRUE);
        JRETURN JTRUE;
    }
};

JINT main() {
    JDM::SetRandomSeed();
    JMS<BomberMan>()->Start();
    JRETURN JFALSE;
}
