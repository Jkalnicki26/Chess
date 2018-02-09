#include <iostream>
#include <vector>
#include <string>

#define BOARDWIDTH 8
#define BOARDHEIGHT 8

#define BLACK  1		//Direction of movement as well as player id
#define WHITE  -1

using namespace std;

class Point
{
public:
    int r;
    int c;
    
    Point(int y, int x)
    {
        r = y;
        c = x;
    }
    
    Point() {
        r = -1;
        c = -1;
    }
};

class ChessPoint : public Point
{
public:
    int getR() {
        return r;
    }
    int getC() {
        return c;
    }
    
    //Description: Check 0 <= val < 8 before setting
    //Returns: True if set was successful (ie: val is between 0 and 8)
    bool setR(int val) {
        if (val >= 0 && val < BOARDHEIGHT)
        {
            r = val;
            return true;
        }
        return false;
    }
    
    bool setC(int val) {
        if (val >= 0 && val < BOARDWIDTH)
        {
            c = val;
            return true;
        }
        return false;
    }
    
    ChessPoint(Point pos) {
        setR(pos.r);
        setC(pos.c);
    }
    
    ChessPoint(int r, int c) {
        setR(r);
        setC(c);
    }
};

class ChessPiece
{
private:
    int			playerColor;
    
protected:
    ChessPoint  myPos;
    
public:
    ChessPiece(int color, ChessPoint pos) : myPos(pos)
    {
        playerColor = color;
    }
    
    int getColor() { return playerColor; }
    int getDir() { return playerColor; }
    virtual bool validMove(Point pos) { return true; }
    virtual bool doMove(Point pos)
    {
        if (validMove(pos))
            return (myPos.setR(pos.r) && myPos.setC(pos.c));
        else
            return false;
    }
};

class PiecePawn : public ChessPiece
{
private:
    bool firstMove;
    
public:
    PiecePawn(int color, ChessPoint pos) : ChessPiece(color, pos) {
        firstMove = true;
    }
    
    bool validMove(Point pos) {
        if ( (pos.c == myPos.getC() && pos.r == myPos.getR() + getDir()) ||
            (pos.c == myPos.getC() && pos.r == myPos.getR() + getDir()*2 && firstMove)
            )
            return true;
        else
            return false;
    }
    
    bool doMove(Point pos) {
        if (ChessPiece::doMove(pos))
        {
            firstMove = false;
            return true;
        }
        else
            return false;
    }
};

class PieceBishop : public ChessPiece
{
    
public:
    PieceBishop(int color, ChessPoint pos) : ChessPiece(color, pos) {
    }
    
    bool validMove(Point pos) {
        if((myPos.getR() < 0 || myPos.getR() > 7) || (myPos.getC() < 0 || myPos.getC() > 7))
            if((myPos.getR() > pos.r || myPos.getR() < pos.r) && (myPos.getC() > pos.c || myPos.getC() < pos.c))
                if((pos.r - myPos.getR() == pos.c - myPos.getC()) || (pos.r + myPos.getR() == pos.c + myPos.getC()))
                    return true;
                else
                    return false;
            else
                return false;
        else
            return false;

    }
    
    bool doMove(Point pos) {
        if (ChessPiece::doMove(pos))
        {
            return true;
        }
        else;
            return false;
    }
};



int main()
{
    vector<ChessPiece> whitePieces;
    vector<ChessPiece> blackPieces;
    
    //Make all the white pieces
    for (int c = 0; c < BOARDWIDTH; c++) {
        ChessPoint newPos(BOARDHEIGHT - 2, c);
        whitePieces.push_back(PiecePawn(WHITE, newPos));
        whitePieces.push_back(PieceBishop(WHITE, newPos));
    }
    
    //Make all the black pieces
    for (int c = 0; c < BOARDWIDTH; c++) {
        ChessPoint newPos(1, c);
        blackPieces.push_back(PiecePawn(BLACK, newPos));
        blackPieces.push_back(PieceBishop(BLACK, newPos));
    }
    
    return 0;
}
