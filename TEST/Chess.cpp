#include "JDM.hpp"

JCLASS ConsoleExample : JPUBLIC JWINDOW {
JPRIVATE:

    JCINT TileSize = 10;
    JSTATIC JCINT Width = 8;
    JSTATIC JCINT Height = 8;

    JSTRUCT Piece { JINT Index; JBOOL AlreadyMove = JFALSE; };

    JENUM ChessValue{
        VPON = 100,
        VKNIGHT = 300,
        VBISHOP = 300,
        VROOK = 500,
        VQUEEN = 900,
        VKING = 1000
    };
    JENUM ChessPiece{
        PON = 0x1, ROOK = 0x2,
        KNIGHT = 0x3, BISHOP = 0x4,
        QUEEN = 0x5, KING = 0x6,

        BLACK = 0x10,
        WHITE = 0x20
    };

    JENUM Offset {
        LEFT = -1, RIGHT = 1,
        DOWN = 8, UP = -8,
        LUP = -9, RUP = -7,
        LDOWN = 7, RDOWN = 9,
    };

    JINT Depth = 2;
    JFLOAT TurnTime = .5f;
    JINT NumOfMoves = 0;
    JWSTR WhiteChessPiece[6];
    JWSTR BlackChessPiece[6];
    JINT Squares[Width * Height];
    JINT CurrentSelected = -1;
    JINT SelectedPiece = 0;
    JCCHAR *StartPositionFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    JCCHAR *CustomPositionFEN = "rnbqkbnr/8/8/8/8/8/8/RNBQKBNR";

    JINT TEST = 0;
    JBOOL CheckSession = JFALSE;
    JINT NumOfAllLegalMoves = 0;
    JVECTOR<JPAIR<JINT, JVECTOR<JINT>>> CurrentLegalMoves;
    JVECTOR<JPAIR<JINT, JVECTOR<JINT>>> PseudoLegalMoves;
    JVECTOR<Piece> AllPiece;

JPUBLIC:
    ConsoleExample() : JWINDOW("ConsoleExample", 80, 80, 8, 8) { }
    JBOOL onUserCreate() {
        GetSpriteString(WhiteChessPiece[0], "ChessPiece/Wpon.sprt");
        GetSpriteString(WhiteChessPiece[1], "ChessPiece/Wrook.sprt");
        GetSpriteString(WhiteChessPiece[2], "ChessPiece/Wknight.sprt");
        GetSpriteString(WhiteChessPiece[3], "ChessPiece/Wbishop.sprt");
        GetSpriteString(WhiteChessPiece[4], "ChessPiece/Wqueen.sprt");
        GetSpriteString(WhiteChessPiece[5], "ChessPiece/Wking.sprt");

        GetSpriteString(BlackChessPiece[0], "ChessPiece/Bpon.sprt");
        GetSpriteString(BlackChessPiece[1], "ChessPiece/Brook.sprt");
        GetSpriteString(BlackChessPiece[2], "ChessPiece/Bknight.sprt");
        GetSpriteString(BlackChessPiece[3], "ChessPiece/Bbishop.sprt");
        GetSpriteString(BlackChessPiece[4], "ChessPiece/Bqueen.sprt");
        GetSpriteString(BlackChessPiece[5], "ChessPiece/Bking.sprt");

        LoadPositionFEN(StartPositionFEN);
        CheckAllLegalMove();
        JRETURN JTRUE;
    }

    JVOID ResetBoard() {
        JFOR (JINT r = 0; r < Height; r++)
        JFOR (JINT c = 0; c < Width; c++)
        Squares[r * Width + c] = 0;
    }

    JVOID LoadPositionFEN(JCCHAR * Fen) {
        ResetBoard();
        JINT Index = 0;
        JINT SquareIndex = 0;
        CHAR CurrentChar;
        JDO {
            CurrentChar = Fen[Index++];
            JSWITCH (CurrentChar) {
                JCASE 'P' : Squares[SquareIndex++] = ChessPiece::WHITE | ChessPiece::PON;
                    AllPiece.push_back({SquareIndex - 1}); JBREAK;
                JCASE 'R' : Squares[SquareIndex++] = ChessPiece::WHITE | ChessPiece::ROOK;
                    AllPiece.push_back({SquareIndex - 1}); JBREAK;
                JCASE 'N' : Squares[SquareIndex++] = ChessPiece::WHITE | ChessPiece::KNIGHT;
                    AllPiece.push_back({SquareIndex - 1}); JBREAK;
                JCASE 'B' : Squares[SquareIndex++] = ChessPiece::WHITE | ChessPiece::BISHOP;
                    AllPiece.push_back({SquareIndex - 1}); JBREAK;
                JCASE 'Q' : Squares[SquareIndex++] = ChessPiece::WHITE | ChessPiece::QUEEN;
                    AllPiece.push_back({SquareIndex - 1}); JBREAK;
                JCASE 'K' : Squares[SquareIndex++] = ChessPiece::WHITE | ChessPiece::KING;
                    AllPiece.push_back({SquareIndex - 1}); JBREAK;
                JCASE 'p' : Squares[SquareIndex++] = ChessPiece::BLACK | ChessPiece::PON;
                    AllPiece.push_back({SquareIndex - 1}); JBREAK;
                JCASE 'r' : Squares[SquareIndex++] = ChessPiece::BLACK | ChessPiece::ROOK;
                    AllPiece.push_back({SquareIndex - 1}); JBREAK;
                JCASE 'n' : Squares[SquareIndex++] = ChessPiece::BLACK | ChessPiece::KNIGHT;
                    AllPiece.push_back({SquareIndex - 1}); JBREAK;
                JCASE 'b' : Squares[SquareIndex++] = ChessPiece::BLACK | ChessPiece::BISHOP;
                    AllPiece.push_back({SquareIndex - 1}); JBREAK;
                JCASE 'q' : Squares[SquareIndex++] = ChessPiece::BLACK | ChessPiece::QUEEN;
                    AllPiece.push_back({SquareIndex - 1}); JBREAK;
                JCASE 'k' : Squares[SquareIndex++] = ChessPiece::BLACK | ChessPiece::KING;
                    AllPiece.push_back({SquareIndex - 1}); JBREAK;
                JCASE ' ' : Squares[SquareIndex++] = 0;
                JDEFAULT: JIF (isdigit(CurrentChar)) { JINT Digit = CurrentChar - '0';
                        JFOR (JINT i = 0; i < Digit; i++) Squares[SquareIndex++] = 0;
                    } JBREAK;
            }
        } JWHILE(SquareIndex < 64 && CurrentChar != 0);
    }

    JWSTR GetString(JINT Piece) {
        JSWITCH(Piece){
            JCASE ChessPiece::WHITE | ChessPiece::PON : JRETURN WhiteChessPiece[0]; JBREAK;
            JCASE ChessPiece::WHITE | ChessPiece::ROOK: JRETURN WhiteChessPiece[1]; JBREAK;
            JCASE ChessPiece::WHITE | ChessPiece::KNIGHT: JRETURN WhiteChessPiece[2]; JBREAK;
            JCASE ChessPiece::WHITE | ChessPiece::BISHOP: JRETURN WhiteChessPiece[3]; JBREAK;
            JCASE ChessPiece::WHITE | ChessPiece::QUEEN: JRETURN WhiteChessPiece[4]; JBREAK;
            JCASE ChessPiece::WHITE | ChessPiece::KING: JRETURN WhiteChessPiece[5]; JBREAK;
            JCASE ChessPiece::BLACK | ChessPiece::PON: JRETURN BlackChessPiece[0]; JBREAK;
            JCASE ChessPiece::BLACK | ChessPiece::ROOK: JRETURN BlackChessPiece[1]; JBREAK;
            JCASE ChessPiece::BLACK | ChessPiece::KNIGHT: JRETURN BlackChessPiece[2]; JBREAK;
            JCASE ChessPiece::BLACK | ChessPiece::BISHOP: JRETURN BlackChessPiece[3]; JBREAK;
            JCASE ChessPiece::BLACK | ChessPiece::QUEEN: JRETURN BlackChessPiece[4]; JBREAK;
            JCASE ChessPiece::BLACK | ChessPiece::KING: JRETURN BlackChessPiece[5]; JBREAK;
        }
    }

    JVECTOR<JINT> SlidingPiece(JINT Piece, JINT Index, JBOOL ReadOnly = JFALSE) {
        JVECTOR<JINT> Moves;
        JINT NewPiece = Piece % 0x10;
        JBOOL LeftBool      = Any(ChessPiece::ROOK == NewPiece, ChessPiece::QUEEN == NewPiece, ChessPiece::KING == NewPiece);
        JBOOL RightBool     = Any(ChessPiece::ROOK == NewPiece, ChessPiece::QUEEN == NewPiece, ChessPiece::KING == NewPiece);
        JBOOL UpBool        = Any(ChessPiece::ROOK == NewPiece, ChessPiece::QUEEN == NewPiece, ChessPiece::KING == NewPiece,
                                  (ChessPiece::PON | ChessPiece::WHITE) == Piece);
        JBOOL DownBool      = Any(ChessPiece::ROOK == NewPiece, ChessPiece::QUEEN == NewPiece, ChessPiece::KING == NewPiece,
                                  (ChessPiece::PON | ChessPiece::BLACK) == Piece);
        JBOOL UpLeftBool    = Any(ChessPiece::BISHOP == NewPiece, ChessPiece::QUEEN == NewPiece, ChessPiece::KING == NewPiece);;
        JBOOL UpRightBool   = Any(ChessPiece::BISHOP == NewPiece, ChessPiece::QUEEN == NewPiece, ChessPiece::KING == NewPiece);;
        JBOOL DownLeftBool  = Any(ChessPiece::BISHOP == NewPiece, ChessPiece::QUEEN == NewPiece, ChessPiece::KING == NewPiece);;
        JBOOL DownRightBool = Any(ChessPiece::BISHOP == NewPiece, ChessPiece::QUEEN == NewPiece, ChessPiece::KING == NewPiece);;
        JINT Step = (NewPiece == ChessPiece::KING) ? 2 : ((NewPiece == ChessPiece::PON) ? ((isPieceAlreadyMove(Index)) ? 2 : 3) : 8);
        JFOR(JINT i = 1; i < Step; i++) {
            JINT LeftIndex      = (Index + (i * Offset::LEFT));
            JINT RightIndex     = (Index + (i * Offset::RIGHT));
            JINT UpIndex        = (Index + (i * Offset::UP));
            JINT DownIndex      = (Index + (i * Offset::DOWN));
            JINT UpLeftIndex    = (Index + (i * Offset::LUP));
            JINT UpRightIndex   = (Index + (i * Offset::RUP));
            JINT DownLeftIndex  = (Index + (i * Offset::LDOWN));
            JINT DownRightIndex = (Index + (i * Offset::RDOWN));
            JIF(LeftBool) { LeftBool = LeftCheck(LeftIndex); JIF (LeftBool) {
                JIF (ReadOnly) {
                    JIF (Squares[LeftIndex] != 0) { LeftBool = JFALSE;
                    JIF(CheckIFKingWillBeEaten(Piece, LeftIndex)) { CheckSession = JTRUE; JRETURN Moves; }
                }} JELSE LeftBool = CheckIfGood(LeftIndex, Piece, Index, Moves); }
            }
            JIF(RightBool) { RightBool = RightCheck(RightIndex); JIF (RightBool) {
                JIF (ReadOnly) {
                    JIF (Squares[RightIndex] != 0) { RightBool = JFALSE;
                    JIF(CheckIFKingWillBeEaten(Piece, RightIndex)) { CheckSession = JTRUE; JRETURN Moves; }
                }} JELSE RightBool = CheckIfGood(RightIndex, Piece, Index, Moves); }
            }
            JIF(UpBool) { UpBool = UpCheck(UpIndex); JIF (UpBool) {
                JIF (ReadOnly) {
                    JIF (Squares[UpIndex] != 0) { UpBool = JFALSE;
                    JIF(CheckIFKingWillBeEaten(Piece, UpIndex)) { CheckSession = JTRUE; JRETURN Moves; }
                }} JELSE UpBool = CheckIfGood(UpIndex, Piece, Index, Moves); }
            }
            JIF(DownBool) { DownBool = DownCheck(DownIndex); JIF (DownBool) {
                JIF (ReadOnly) {
                    JIF (Squares[DownIndex] != 0) { DownBool = JFALSE;
                    JIF(CheckIFKingWillBeEaten(Piece, DownIndex)) { CheckSession = JTRUE; JRETURN Moves; }
                }} JELSE DownBool = CheckIfGood(DownIndex, Piece, Index, Moves); }
            }
            JIF(UpLeftBool) { UpLeftBool = ULeftCheck(UpLeftIndex); JIF (UpLeftBool) {
                JIF (ReadOnly) {
                    JIF (Squares[UpLeftIndex] != 0) { UpLeftBool = JFALSE;
                    JIF(CheckIFKingWillBeEaten(Piece, UpLeftIndex)) { CheckSession = JTRUE; JRETURN Moves; }
                }} JELSE UpLeftBool = CheckIfGood(UpLeftIndex, Piece, Index, Moves); }
            }
            JIF(UpRightBool) { UpRightBool = URightCheck(UpRightIndex); JIF (UpRightBool) {
                JIF (ReadOnly) {
                    JIF (Squares[UpRightIndex] != 0) { UpRightBool = JFALSE;
                    JIF(CheckIFKingWillBeEaten(Piece, UpRightIndex)) { CheckSession = JTRUE; JRETURN Moves; }
                }} JELSE UpRightBool = CheckIfGood(UpRightIndex, Piece, Index, Moves); }
            }
            JIF(DownLeftBool) { DownLeftBool = DLeftCheck(DownLeftIndex); JIF (DownLeftBool) {
                JIF (ReadOnly) {
                    JIF (Squares[DownLeftIndex] != 0) { DownLeftBool = JFALSE;
                    JIF(CheckIFKingWillBeEaten(Piece, DownLeftIndex)) { CheckSession = JTRUE; JRETURN Moves; }
                }} JELSE DownLeftBool = CheckIfGood(DownLeftIndex, Piece, Index, Moves); }
            }
            JIF(DownRightBool) { DownRightBool = DRightCheck(DownRightIndex); JIF (DownRightBool) {
                JIF (ReadOnly) {
                    JIF (Squares[DownRightIndex] != 0) { DownRightBool = JFALSE;
                    JIF(CheckIFKingWillBeEaten(Piece, DownRightIndex)) { CheckSession = JTRUE; JRETURN Moves; }
                }} JELSE DownRightBool = CheckIfGood(DownRightIndex, Piece, Index, Moves); }
            }
        }
        JRETURN Moves;
    }

    JBOOL CheckIFKingWillBeEaten(JINT Piece, JINT Index) {
        JRETURN((Piece < ChessPiece::WHITE) ? (Squares[Index] == (ChessPiece::WHITE | ChessPiece::KING))
                                            : (Squares[Index] == (ChessPiece::BLACK | ChessPiece::KING)));
    }

    JBOOL isPieceAlreadyMove(JINT Index) {
        JFOR (JAUTO Pon : AllPiece) 
            JIF(Pon.Index == Index) JRETURN Pon.AlreadyMove;
        JRETURN JFALSE;
    }

    JBOOL UpCheck    (JINT Index) { JRETURN Index >= 0; }
    JBOOL DownCheck  (JINT Index) { JRETURN Index < 64; }
    JBOOL LeftCheck  (JINT Index) { JRETURN (Index >= 0 && Index % 8 != 7); }
    JBOOL RightCheck (JINT Index) { JRETURN (Index < 64 && (Index + 1) % 8 != 1); }
    JBOOL ULeftCheck (JINT Index) { JRETURN (Index >= 0 && Index % 8 != 7 && Index >= 0); }
    JBOOL URightCheck(JINT Index) { JRETURN (Index < 64 && (Index + 1) % 8 != 1 && Index >= 0); }
    JBOOL DLeftCheck (JINT Index) { JRETURN (Index >= 0 && Index % 8 != 7 && Index < 64); }
    JBOOL DRightCheck(JINT Index) { JRETURN (Index < 64 && (Index + 1) % 8 != 1 && Index < 64); }

    JVECTOR<JINT> PonMove(JINT Piece, JINT Index, JBOOL ReadOnly = JFALSE) {
        JVECTOR<JINT> Moves;
        JIF (!ReadOnly) Moves = SlidingPiece(Piece, Index);
        JINT Left = Index + Offset::LEFT + ((Piece < ChessPiece::WHITE) ? Offset::DOWN : Offset::UP);
        JINT Right = Index + Offset::RIGHT + ((Piece < ChessPiece::WHITE) ? Offset::DOWN : Offset::UP);
        JIF(((Piece < ChessPiece::WHITE) ? DLeftCheck(Left) : ULeftCheck(Left)) && Squares[Left] != 0 &&
            CheckIfInverseColor(Squares[Left], Piece)) {
                JIF(ReadOnly) { JIF(CheckIFKingWillBeEaten(Piece, Left)) { CheckSession = JTRUE; JRETURN Moves; } }
                JELSE JIF(isValidMove(Left, Index)) Moves.push_back(Left);
            }
        JIF(((Piece < ChessPiece::WHITE) ? DRightCheck(Right) : URightCheck(Right)) && Squares[Right] != 0 &&
            CheckIfInverseColor(Squares[Right], Piece)) {
                JIF(ReadOnly) { JIF(CheckIFKingWillBeEaten(Piece, Right)) { CheckSession = JTRUE; JRETURN Moves; } }
                JELSE JIF(isValidMove(Right, Index)) Moves.push_back(Right);
            }
        JRETURN Moves;
    }

    JVECTOR<JINT> KingMove(JINT Piece, JINT Index, JBOOL ReadOnly = JFALSE) {
        JVECTOR<JINT> Moves = SlidingPiece(Piece, Index);
        JIF (!isPieceAlreadyMove(Index)) {
            JIF (All(LeftCheck(Index + (1 * Offset::LEFT)) && Squares[Index + (1 * Offset::LEFT)] == 0,
                     LeftCheck(Index + (2 * Offset::LEFT)) && Squares[Index + (2 * Offset::LEFT)] == 0,
                     LeftCheck(Index + (3 * Offset::LEFT)) && Squares[Index + (3 * Offset::LEFT)] == 0,
                     LeftCheck(Index + (4 * Offset::LEFT)) && Squares[Index + (4 * Offset::LEFT)] != 0,
                     Squares[Index + (4 * Offset::LEFT)] == (
                        (Piece < ChessPiece::WHITE) ? (ChessPiece::BLACK | ChessPiece::ROOK) : (ChessPiece::WHITE | ChessPiece::ROOK)))) {
                    JIF(!isPieceAlreadyMove(Index + (4 * Offset::LEFT)) && isValidMove(Index + (2 * Offset::LEFT), Index)) Moves.push_back(Index + (2 * Offset::LEFT));
            }
            JIF (All(RightCheck(Index + (1 * Offset::RIGHT)) && Squares[Index + (1 * Offset::RIGHT)] == 0,
                     RightCheck(Index + (2 * Offset::RIGHT)) && Squares[Index + (2 * Offset::RIGHT)] == 0,
                     RightCheck(Index + (3 * Offset::RIGHT)) && Squares[Index + (3 * Offset::RIGHT)] != 0,
                     Squares[Index + (3 * Offset::RIGHT)] == (
                        (Piece < ChessPiece::WHITE) ? (ChessPiece::BLACK | ChessPiece::ROOK) : (ChessPiece::WHITE | ChessPiece::ROOK)))) {
                    JIF(!isPieceAlreadyMove(Index + (3 * Offset::RIGHT)) && isValidMove(Index + (2 * Offset::RIGHT), Index)) Moves.push_back(Index + (2 * Offset::RIGHT));
            }
        }
        JRETURN Moves;
    }

    JVECTOR<JINT> KnightMove(JINT Piece, JINT Index, JBOOL ReadOnly = JFALSE) {
        JVECTOR<JINT> Moves;
        JINT x = Index % Width;
        JINT y = Index / Width;
        JIF ((x + 1) >= 0 && (x + 1) < 8 && (y + 2) < 8 && (y + 2) >= 0)
            JIF (CheckIfInverseColor(Piece, Squares[(x + 1) + (y + 2) * Width]) || Squares[(x + 1) + (y + 2) * Width] == 0) {
                JIF (ReadOnly) { JIF (CheckIFKingWillBeEaten(Piece, ((x + 1) + (y + 2) * Width))) { CheckSession = JTRUE; JRETURN Moves; } }
                JELSE JIF(isValidMove(((x + 1) + (y + 2) * Width), Index)) Moves.push_back((x + 1) + (y + 2) * Width);
        }
        JIF ((x + 1) >= 0 && (x + 1) < 8 && (y - 2) < 8 && (y - 2) >= 0)
            JIF (CheckIfInverseColor(Piece, Squares[(x + 1) + (y - 2) * Width]) || Squares[(x + 1) + (y - 2) * Width] == 0) {
                JIF (ReadOnly) { JIF (CheckIFKingWillBeEaten(Piece, ((x + 1) + (y - 2) * Width))) { CheckSession = JTRUE; JRETURN Moves; } }
                JELSE JIF(isValidMove(((x + 1) + (y - 2) * Width), Index)) Moves.push_back((x + 1) + (y - 2) * Width);
        }
        JIF ((x - 1) >= 0 && (x - 1) < 8 && (y + 2) < 8 && (y + 2) >= 0)
            JIF (CheckIfInverseColor(Piece, Squares[(x - 1) + (y + 2) * Width]) || Squares[(x - 1) + (y + 2) * Width] == 0) {
                JIF (ReadOnly) { JIF (CheckIFKingWillBeEaten(Piece, ((x - 1) + (y + 2) * Width))) { CheckSession = JTRUE; JRETURN Moves; } }
                JELSE JIF(isValidMove(((x - 1) + (y + 2) * Width), Index)) Moves.push_back((x - 1) + (y + 2) * Width);
        }
        JIF ((x - 1) >= 0 && (x - 1) < 8 && (y - 2) < 8 && (y - 2) >= 0)
            JIF (CheckIfInverseColor(Piece, Squares[(x - 1) + (y - 2) * Width]) || Squares[(x - 1) + (y - 2) * Width] == 0) {
                JIF (ReadOnly) { JIF (CheckIFKingWillBeEaten(Piece, ((x - 1) + (y - 2) * Width))) { CheckSession = JTRUE; JRETURN Moves; } }
                JELSE JIF(isValidMove(((x - 1) + (y - 2) * Width), Index)) Moves.push_back((x - 1) + (y - 2) * Width);
        }
        JIF ((x + 2) >= 0 && (x + 2) < 8 && (y + 1) < 8 && (y + 1) >= 0)
            JIF (CheckIfInverseColor(Piece, Squares[(x + 2) + (y + 1) * Width]) || Squares[(x + 2) + (y + 1) * Width] == 0) {
                JIF (ReadOnly) { JIF (CheckIFKingWillBeEaten(Piece, ((x + 2) + (y + 1) * Width))) { CheckSession = JTRUE; JRETURN Moves; } }
                JELSE JIF(isValidMove(((x + 2) + (y + 1) * Width), Index)) Moves.push_back((x + 2) + (y + 1) * Width);
        }
        JIF ((x + 2) >= 0 && (x + 2) < 8 && (y - 1) < 8 && (y - 1) >= 0)
            JIF (CheckIfInverseColor(Piece, Squares[(x + 2) + (y - 1) * Width]) || Squares[(x + 2) + (y - 1) * Width] == 0) {
                JIF (ReadOnly) { JIF (CheckIFKingWillBeEaten(Piece, ((x + 2) + (y - 1) * Width))) { CheckSession = JTRUE; JRETURN Moves; } }
                JELSE JIF(isValidMove(((x + 2) + (y - 1) * Width), Index)) Moves.push_back((x + 2) + (y - 1) * Width);
        }
        JIF ((x - 2) >= 0 && (x - 2) < 8 && (y + 1) < 8 && (y + 1) >= 0)
            JIF (CheckIfInverseColor(Piece, Squares[(x - 2) + (y + 1) * Width]) || Squares[(x - 2) + (y + 1) * Width] == 0) {
                JIF (ReadOnly) { JIF (CheckIFKingWillBeEaten(Piece, ((x - 2) + (y + 1) * Width))) { CheckSession = JTRUE; JRETURN Moves; } }
                JELSE JIF(isValidMove(((x - 2) + (y + 1) * Width), Index)) Moves.push_back((x - 2) + (y + 1) * Width);
        }
        JIF ((x - 2) >= 0 && (x - 2) < 8 && (y - 1) < 8 && (y - 1) >= 0)
            JIF (CheckIfInverseColor(Piece, Squares[(x - 2) + (y - 1) * Width]) || Squares[(x - 2) + (y - 1) * Width] == 0) {
                JIF (ReadOnly) { JIF (CheckIFKingWillBeEaten(Piece, ((x - 2) + (y - 1) * Width))) { CheckSession = JTRUE; JRETURN Moves; } }
                JELSE JIF(isValidMove(((x - 2) + (y - 1) * Width), Index)) Moves.push_back((x - 2) + (y - 1) * Width);
        }

        JRETURN Moves;
    }

    JBOOL CheckIfGood(JINT Index, JINT Piece, JINT From, JVECTOR<JINT> &Moves) {
        JINT CPiece = Squares[Index];
        JIF (CPiece == 0) { JIF(isValidMove(Index, From)) Moves.push_back(Index); JRETURN JTRUE;
        } JELSE JIF (Piece % 0x10 != ChessPiece::PON && CheckIfInverseColor(CPiece, Piece))
            JIF(isValidMove(Index, From)) Moves.push_back(Index);
        JRETURN JFALSE;
    }

    JBOOL isOverlapped(JINT Index) {
        JINT x = Index % Width;
        JINT y = Index / Width;
        JRETURN (x >= 0 && x < 8 && y < 8 && y >= 0);
    }

    JVOID CheckAllLegalMove() {
        NumOfAllLegalMoves = 0;
        CurrentLegalMoves.clear();
        JFOR (JINT y = 0; y < Height; y++)
        JFOR (JINT x = 0; x < Width; x++) {
              JINT Index = (x + y * Width);
              JINT Piece = Squares[Index];
              JIF (Piece != 0 && CheckIfAppropriateToTurn(Piece)) {
                  JSWITCH (Piece % 0x10) {
                      JCASE ChessPiece::ROOK : CurrentLegalMoves.push_back(JMPAIR(Index, SlidingPiece(Piece, Index))); JBREAK;
                      JCASE ChessPiece::BISHOP : CurrentLegalMoves.push_back(JMPAIR(Index, SlidingPiece(Piece, Index))); JBREAK;
                      JCASE ChessPiece::QUEEN : CurrentLegalMoves.push_back(JMPAIR(Index, SlidingPiece(Piece, Index))); JBREAK;
                      JCASE ChessPiece::KING : CurrentLegalMoves.push_back(JMPAIR(Index, KingMove(Piece, Index))); JBREAK;
                      JCASE ChessPiece::KNIGHT : CurrentLegalMoves.push_back(JMPAIR(Index, KnightMove(Piece, Index))); JBREAK;
                      JCASE ChessPiece::PON : CurrentLegalMoves.push_back(JMPAIR(Index, PonMove(Piece, Index))); JBREAK;
                  }
                  NumOfAllLegalMoves += CurrentLegalMoves[CurrentLegalMoves.size() - 1].second.size();
              }
        }
    }

    JBOOL isValidMove(JINT To, JINT From) {
        JINT OldFrom = Squares[From];
        JINT OldTo = Squares[To];
        Squares[To] = Squares[From];
        Squares[From] = 0;
        NumOfMoves++;
        CheckSession = JFALSE;
        JFOR (JINT y = 0; y < Height; y++)
        JFOR (JINT x = 0; x < Width; x++) {
              JIF(CheckSession) {
                  Squares[From] = OldFrom;
                  Squares[To] = OldTo;
                  NumOfMoves--;
                  JRETURN !CheckSession;
              }
              JINT Index = (x + y * Width);
              JINT Piece = Squares[Index];
              JIF (Piece != 0 && CheckIfAppropriateToTurn(Piece)) {
                  JSWITCH (Piece % 0x10) {
                      JCASE ChessPiece::ROOK : SlidingPiece(Piece, Index, JTRUE); JBREAK;
                      JCASE ChessPiece::BISHOP :  SlidingPiece(Piece, Index, JTRUE); JBREAK;
                      JCASE ChessPiece::QUEEN : SlidingPiece(Piece, Index, JTRUE); JBREAK;
                      JCASE ChessPiece::KING : SlidingPiece(Piece, Index, JTRUE); JBREAK;
                      JCASE ChessPiece::KNIGHT : KnightMove(Piece, Index, JTRUE); JBREAK;
                      JCASE ChessPiece::PON : PonMove(Piece, Index, JTRUE); JBREAK;
                  }
            }
        }
        Squares[From] = OldFrom;
        Squares[To] = OldTo;
        NumOfMoves--;
        JRETURN !CheckSession;
     }

    JBOOL CheckIfAppropriateToTurn(JINT Piece) { JRETURN ((NumOfMoves % 2) ? (Piece < ChessPiece::WHITE) : (Piece > ChessPiece::WHITE)); }
    JBOOL CheckIfInverseColor(JINT CPiece, JINT Piece) { JRETURN((CPiece < ChessPiece::WHITE) ? (Piece > ChessPiece::WHITE) : (Piece < ChessPiece::WHITE)); }

    JINT GetPieceIndex(JINT Index) {
        JFOR(JINT i = 0; i < CurrentLegalMoves.size(); i++)
            JIF (CurrentLegalMoves[i].first == Index) JRETURN i;
        JRETURN -1;
    }

    JBOOL isInLegalMoves(JINT Move, JINT Index) {
        JFOR (JAUTO possibleMove : CurrentLegalMoves[Index].second)
            JIF(Move == possibleMove) JRETURN JTRUE;
        JRETURN JFALSE;
    }

    JVOID ChangeIndexPiece(JINT Current, JINT Index) {
        JFOR (JAUTO &Piece : AllPiece) 
            JIF(Piece.Index == Current) {
                Piece.Index = Index;
                Piece.AlreadyMove = JTRUE;
            }
    }

    JINT RandomMove() {
        JIF (NumOfAllLegalMoves > 0) {
            JVECTOR<JINT> AllPieceIndex;
            JFOR (JINT y = 0; y < Height; y++) 
                JFOR(JINT x = 0; x < Width; x++) {
                    JINT Index = (x + y * Width);
                    JINT Piece = Squares[Index];
                    JIF (Piece != 0 && CheckIfAppropriateToTurn(Piece)) {
                        JINT PieceIndex = GetPieceIndex(Index);
                        JIF (PieceIndex != -1 && CurrentLegalMoves[PieceIndex].second.size() > 0) {
                            AllPieceIndex.push_back(Index);
                        }
                    }
                }
 
            JVECTOR<JINT> AllEvaluation;
            JVECTOR<JPAIR<JINT, JINT>> Moves;
            JFOR (JAUTO Index : AllPieceIndex) {
                JINT PieceIndex = GetPieceIndex(Index);
                JFOR (JAUTO Move : CurrentLegalMoves[PieceIndex].second) {
                    JINT OldFrom = Squares[Index];
                    JINT OldTo = Squares[Move];
                    Squares[Move] = Squares[Index];
                    Squares[Index] = 0;
                    Moves.push_back(JMPAIR(Index, Move));
                    AllEvaluation.push_back(Evaluate(OldFrom - (OldFrom % 0x10)));
                    Squares[Index] = OldFrom;
                    Squares[Move] = OldTo;
                }
            }
            JINT Index = 0;
            JBOOL isNotSame = JTRUE;
            JINT MaxValue = AllEvaluation[0];
            JFOR(JINT i = 0; i < AllEvaluation.size(); i++) {
                JIF(MaxValue < AllEvaluation[i]) {
                    isNotSame = JFALSE;
                    Index = i;
                    MaxValue = AllEvaluation[i];
                }
            }
            JIF (isNotSame) {
                JINT RandNum = Random() % AllPieceIndex.size();
                CurrentSelected = AllPieceIndex[RandNum];
                JINT PieceIndex = GetPieceIndex(CurrentSelected);
                JINT RandomMoveIndex = Random() % CurrentLegalMoves[PieceIndex].second.size();
                JINT RandomMove = CurrentLegalMoves[PieceIndex].second[RandomMoveIndex];
                JINT Index = (RandomMove);
                JINT Piece = Squares[CurrentSelected];
                MovePiece(Piece, Index);
            } JELSE {
                CurrentSelected = Moves[Index].first;
                MovePiece(Squares[CurrentSelected], Moves[Index].second);
            }
        }
    }

    JINT Evaluate(JINT Color) {
        JINT White = 0;
        JINT Black = 0;
        JFOR (JINT y = 0; y < Height; y++) {
            JFOR(JINT x = 0; x < Width; x++) {
                JINT Index = (x + y * Width);
                JINT Piece = Squares[Index];
                JIF (Piece < ChessPiece::WHITE)
                    Black += GetValuePiece(Piece);
                JELSE White += GetValuePiece(Piece);
            }
        }
        JINT Score = ((Color == ChessPiece::WHITE) ? (White - Black) : (Black - White));
        JRETURN Score;
    }

    JVOID MovePiece(JINT Piece, JINT Index) {
        JIF(CurrentSelected == Index) CurrentSelected = -1;
        JELSE JIF (Piece != 0 && CurrentSelected != -1 && CheckIfAppropriateToTurn(Piece) &&
            (Squares[Index] == 0 || CheckIfInverseColor(Squares[Index], Piece))) {
            JINT NewIndex = GetPieceIndex(CurrentSelected);
            JIF (NewIndex != - 1 && Squares[Index] != - 1 && isInLegalMoves(Index, NewIndex)) {
                JAUTO Iterator = AllPiece.begin();
                JFOR (; Iterator != AllPiece.end(); Iterator++)
                    JIF ((*Iterator).Index == Index) { AllPiece.erase(Iterator); JBREAK; }
                ChangeIndexPiece(CurrentSelected, Index);
                JIF (Piece % 0x10 == ChessPiece::KING) {
                    JINT Result = Index - CurrentSelected;
                    JIF (Result == 2) {
                        ChangeIndexPiece(Index + 1, Index - 1);
                        Squares[Index - 1] = Squares[Index + 1];
                        Squares[Index + 1] = 0;
                    } JELSE JIF (Result == -2) {
                        ChangeIndexPiece(Index - 2, Index + 1);
                        Squares[Index + 1] = Squares[Index - 2];
                        Squares[Index - 2] = 0;
                    }
                }
                JELSE JIF (Piece % 0x10 == ChessPiece::PON) {
                    JIF((Piece < ChessPiece::WHITE) ? (Index > 55) : (Index < 8)) Piece = PromotePon(Piece);
                }
                Squares[Index] = Piece;
                Squares[CurrentSelected] = 0;
                CurrentSelected = -1;
                NumOfMoves++;
                CheckAllLegalMove();
                JIF (NumOfMoves % 2) RandomMove();
            } JELSE CurrentSelected = Index;
        } JELSE CurrentSelected = Index;
    }

    JINT GetValuePiece(JINT Piece) {
        JSWITCH(Piece % 0x10){
            JCASE ChessPiece::PON : JRETURN ChessValue::VPON; JBREAK;
            JCASE ChessPiece::ROOK: JRETURN ChessValue::VROOK; JBREAK;
            JCASE ChessPiece::KNIGHT : JRETURN ChessValue::VKNIGHT; JBREAK;
            JCASE ChessPiece::BISHOP: JRETURN ChessValue::VBISHOP; JBREAK;
            JCASE ChessPiece::QUEEN: JRETURN ChessValue::VQUEEN; JBREAK;
            JCASE ChessPiece::KING: JRETURN ChessValue::VKING; JBREAK;
        }
    }

    JINT PromotePon(JINT Piece) { JRETURN ((Piece < ChessPiece::WHITE) ? (ChessPiece::BLACK | ChessPiece::QUEEN) : (ChessPiece::WHITE | ChessPiece::QUEEN)); }
    JBOOL onUserUpdate() {
        JIF (NumOfAllLegalMoves <= 0) JRETURN JTRUE;
        JINT MouseX = (MousePos.x / TileSize) / Width;
        JINT MouseY = (MousePos.y / TileSize) / Height;
        // JIF(keyboard.Keys[Keys::J_MOUSE_LEFT].isPressed) {
        //     JIF (MouseX >= 0 && MouseX < 8 && MouseY >= 0 && MouseY < 8) {
        //         JINT Index = (MouseX + MouseY * Width);
        //         JINT Piece = Squares[CurrentSelected];
        //         MovePiece(Piece, Index);
        //     }
        // }

        // TurnTime -= ElapseTime;
        // JIF (TurnTime <= 0) {
        //     TurnTime = .5f;
        //     RandomMove();
        // }

        JINT PieceIndex = GetPieceIndex(CurrentSelected);
        JFOR (JINT y = 0; y < Height; y++) {
            JFOR(JINT x = 0; x < Width; x++) {
                JINT SquareValue = Squares[y * Width + x];
                DrawBox({TileSize, TileSize, JSTATICC<JFLOAT>(x * TileSize), JSTATICC<JFLOAT>(y * TileSize)}, PIXEL_SOLID,
                    ((y * Width + x) != CurrentSelected) ? (((x + y) % 2 == 0) ? FG_GRAY : FG_DARK_CYAN) :
                        ((PieceIndex != -1) ? FG_DARK_GREEN : FG_RED), JTRUE);
            }
        }

        JIF (CurrentSelected != -1 && Squares[CurrentSelected] != 0) {
            JIF (PieceIndex != -1) {
                Drawer::DrawBoxHollow(JTHIS, {TileSize, TileSize,
                    JSTATICC<JFLOAT>((CurrentSelected % Width) * TileSize),
                    JSTATICC<JFLOAT>((CurrentSelected / Width) * TileSize)}, 1,
                        PIXEL_SOLID, FG_GREEN, JTRUE);
                JFOR (JAUTO possibleMove : CurrentLegalMoves[PieceIndex].second) {
                    JINT x = possibleMove % Width;
                    JINT y = possibleMove / Width;
                    DrawBox({TileSize, TileSize, JSTATICC<JFLOAT>(x * TileSize), JSTATICC<JFLOAT>(y * TileSize)}, PIXEL_SOLID, FG_DARK_GREEN, JTRUE);
                    Drawer::DrawBoxHollow(JTHIS, {TileSize, TileSize, JSTATICC<JFLOAT>(x * TileSize), JSTATICC<JFLOAT>(y * TileSize)}, 1,
                        PIXEL_SOLID, FG_GREEN, JTRUE);
                }
            }
        }
        Drawer::DrawBoxHollow(JTHIS, {TileSize, TileSize, JSTATICC<JFLOAT>(MouseX * TileSize), JSTATICC<JFLOAT>(MouseY * TileSize)}, 1,
            PIXEL_SOLID, ((PieceIndex != -1) ? ((isInLegalMoves(MouseX + MouseY * Width, PieceIndex)) ? FG_CYAN : FG_DARK_RED) : FG_DARK_RED), JTRUE);
        JFOR (JINT y = 0; y < Height; y++) {
            JFOR(JINT x = 0; x < Width; x++) {
                JINT SquareValue = Squares[y * Width + x];               
                JIF (SquareValue != 0) {
                    DrawCString({JSTATICC<JFLOAT>(x * TileSize), JSTATICC<JFLOAT>(y * TileSize)}, GetString(SquareValue), JTRUE);
                }
            }
        }

        DrawString({0, 0}, JTOWSTR(TEST), FG_WHITE, JTRUE);
        JRETURN JTRUE;
    }
};

JINT main() {
    JDM::SetRandomSeed();
    JMS<ConsoleExample>()->Start();
    JRETURN JFALSE;
}
