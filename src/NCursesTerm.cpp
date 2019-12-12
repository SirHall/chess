#include "NCursesTerm.hpp"

short GetColorPair(Board &board, std::uint_fast8_t index)
{
    std::uint_fast8_t x = 0;
    std::uint_fast8_t y = 0;
    board.IndexToPos(index, x, y);
    bool  isBlackSquare = ((x + y) % 2) == 0;
    Piece piece;
    if (board.GetPieceAtPos(index, piece))
    {
        if (piece.GetColor() == Color::Blue)
            return isBlackSquare ? BLUE_ON_BLACK : BLUE_ON_WHITE;
        else
            return isBlackSquare ? RED_ON_BLACK : RED_ON_WHITE;
    }
    else // There is nothing here
        return isBlackSquare ? BLUE_ON_BLACK : BLUE_ON_WHITE;
}

char GetPieceSymbol(PieceType type)
{
    char symbols[7];
    symbols[PieceType::None]   = ' ';
    symbols[PieceType::Pawn]   = 'P';
    symbols[PieceType::Rook]   = 'R';
    symbols[PieceType::Bishop] = 'B';
    symbols[PieceType::Knight] = 'N';
    symbols[PieceType::King]   = 'K';
    symbols[PieceType::Queen]  = 'Q';

    return symbols[type];
}

NCursesTerm::NCursesTerm()
{
    // Start curses mode
    initscr();
    // Disable line buffering, but allow keyboard singal shortcuts
    cbreak();
    // Prevent pressed keys from being typed onto the screen
    noecho();
    // Enable special keys
    keypad(stdscr, TRUE);

    if (has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color\n");
        std::exit(1);
    }
    start_color();

    init_pair(BLUE_ON_WHITE, COLOR_BLUE, COLOR_WHITE);
    init_pair(BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK);
    init_pair(RED_ON_WHITE, COLOR_RED, COLOR_WHITE);
    init_pair(RED_ON_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(DEBUG_PAIR, COLOR_YELLOW, COLOR_GREEN);
}

NCursesTerm::NCursesTerm(const NCursesTerm &other) {}

NCursesTerm::NCursesTerm(NCursesTerm &&other) {}

NCursesTerm &NCursesTerm::operator=(const NCursesTerm &other) { return *this; }

NCursesTerm &NCursesTerm::operator=(NCursesTerm &&other) { return *this; }

NCursesTerm::~NCursesTerm() { endwin(); }

void NCursesTerm::Draw() { refresh(); }

void NCursesTerm::DrawBoard(Board &board)
{
    // int boardX = 3;
    // int boardY = 3;

    // Draw board itself
    for (int x = 0; x < 12; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            move(y, x);

            // Draw board itself
            if (x >= 2 && x < 10 && y >= 2 && y < 10)
            {
                std::uint_fast8_t pieceIndex =
                    board.PosToIndex(x - 2, 7 - (y - 2));
                short colorPair = GetColorPair(board, pieceIndex);
                attron(COLOR_PAIR(colorPair));
                Piece piece;
                board.GetPieceAtPos(pieceIndex, piece);
                addch(GetPieceSymbol(piece.GetType()));

                attroff(COLOR_PAIR(colorPair));
            }
            else // Draw coordinate numbers/letters around the board
            {
                if ((x == 0 || x == 11) && (y > 1 && y < 10))
                    addch('8' - y + 2);
                if ((y == 1 || y == 10) && (x > 1 && x < 10))
                    addch('A' + x - 2);
            }
        }
    }

    // auto moves = board.PossibleMoves(board.CoordToIndex("C1"));
    // attron(COLOR_PAIR(DEBUG_PAIR));
    // for (auto index : moves)
    // {
    //     std::uint_fast8_t x;
    //     std::uint_fast8_t y;
    //     board.IndexToPos(index, x, y);
    //     move(9 - (int)y, (int)x + 2);
    //     addch('\'');
    // }
    // attroff(COLOR_PAIR(DEBUG_PAIR));

    this->Draw();
}