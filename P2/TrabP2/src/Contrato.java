 class Contrato {
     public enum Move {NORT, EAST, SOUTH, WEST, NOOP}

     public enum MazeCell {EMPTY, WALL, START, EXIT}

     public interface IMaze {
         boolean canMove(Pawn pawn, Move move); // true IFF pawn can do move in this maze.

         Move[] getOptions(Pawn pawn);

         // returns the possible moves of pawn.
         void move(Pawn pawn, Move move);

         // if pawn can move, change his position.
         boolean isSolvedBy(Pawn pawn);
         // true IFF pawn is in EXIT position.
     }

     public interface IPawn {
         void move(Move move); // changes this pawn position according to move.

         Route getRoute(); // returns the current route.
     }

     public interface IRoute {
         int getCol();

         // returns the column of the current position.
         int getRow();

         // returns the row of the current position.
         int getCol(int i); // returns the column of the i-th position.

         int getRow(int i); // returns the row of the i-th position.

         int length();

         // returns the number of moves in this route.
         void move(Move move);
// append a new position to this route.
     }
 }