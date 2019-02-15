import java.util.ArrayList;

class Maze implements Contrato.IMaze {

    protected Contrato.MazeCell[][] maze;
    public String name;
    public int numCols;
    public int numRows;


    public Maze(int xSize,int ySize,Contrato.MazeCell[][] maze,String name){
        this.maze = maze;
        this.name=name;
        numCols=xSize;
        numRows=ySize;
    }

    public Contrato.Move[] getOptions(Pawn pawn){
        ArrayList<Contrato.Move> options = new ArrayList<>();
        Route pawnRoute=pawn.getRoute();
        int x =pawnRoute.getCol();
        int y =pawnRoute.getRow();
        Contrato.MazeCell emptyCell= Contrato.MazeCell.EMPTY;
        Contrato.MazeCell endCell = Contrato.MazeCell.EXIT;

        if (canMove(pawn, Contrato.Move.NORT))
            if (maze[x][y-1]==emptyCell||maze[x][y-1]==endCell)
                options.add(Contrato.Move.NORT);

        if (canMove(pawn, Contrato.Move.SOUTH))
            if (maze[x][y+1]==emptyCell||maze[x][y+1]==endCell)
                options.add(Contrato.Move.SOUTH);

        if (canMove(pawn, Contrato.Move.EAST))
            if (maze[x-1][y]==emptyCell||maze[x-1][y]==endCell)
                options.add(Contrato.Move.EAST);

        if (canMove(pawn, Contrato.Move.WEST))
            if (maze[x+1][y]==emptyCell||maze[x+1][y]==endCell)
                options.add(Contrato.Move.WEST);

        //Debuguer
        System.out.print("OP:");
        for (Contrato.Move option:options)
            System.out.print(option+",");
        System.out.println();

        return options.toArray(new Contrato.Move[0]);

    }

    public boolean canMove(Pawn pawn, Contrato.Move move){
        boolean ret=true;
        switch (move){
            case NORT:if(pawn.getRoute().getRow()==0)ret=false;break;
            case SOUTH:if(pawn.getRoute().getRow()==numRows-1)ret=false;break;
            case EAST:if(pawn.getRoute().getCol()==0)ret=false;break;
            case WEST:if (pawn.getRoute().getCol()==numCols-1)ret=false;break;
        }
        return ret;
    }

    public void move(Pawn pawn, Contrato.Move move){
        Contrato.Move[] options =getOptions(pawn);
        for (Contrato.Move option:options) {
            if (canMove(pawn, move)&& move==option) {
                pawn.move(move);
                System.out.println("moves");
                break;
            }
        }
    }

    public boolean isSolvedBy(Pawn pawn){
        int col=pawn.getRoute().getCol();
        int row=pawn.getRoute().getRow();
        if (maze[col][row]==Contrato.MazeCell.EXIT)
            return true;
        return false;
    }

    public int[] getStartPosition(){
        int y=0,x=0;
        while (true){
            if (maze[x][y]== Contrato.MazeCell.START){
                break;
            }
            x++;
            if (x==numCols){
                x=0;
                y++;
            }
        }
        return new int[]{x,y};
    }

    public Pawn solve(){
        int[] start = getStartPosition();
        ArrayList<Pawn> pawns =new ArrayList<>();
        Pawn retPawn =null;
        pawns.add(new Pawn(start[0],start[1]));
        boolean solvedFlag =false;
        while (!solvedFlag){
            ArrayList<Pawn> newPawns=new ArrayList<>();
            int db =0;
            for (Pawn pawn:pawns){
                Route pawnRoute=pawn.getRoute();
                Contrato.Move[] options=getOptions(pawn);
                Contrato.Move lastMove = pawnRoute.route.get(pawnRoute.route.size()-1);
                switch (lastMove){
                    case NORT:lastMove= Contrato.Move.SOUTH;break;
                    case SOUTH:lastMove= Contrato.Move.NORT;break;
                    case EAST:lastMove= Contrato.Move.WEST;break;
                    case WEST:lastMove= Contrato.Move.EAST;break;
                }
                ArrayList<Contrato.Move> newOpions=new ArrayList<>();
                for(Contrato.Move option:options)
                    if(option!=lastMove)
                        newOpions.add(option);
                options=newOpions.toArray(new Contrato.Move[0]);

                if(options.length>0){
                    if(options.length>1)
                        for(int c=1;c<options.length;c++){
                            Pawn newPawn= new Pawn(pawn.getRoute());
                            move(newPawn,options[c]);
                            newPawns.add(newPawn);
                        }
                    move(pawn,options[0]);
                }
                db++;
                System.out.println(db+"->"+pawn.getRoute().getCol()+":"+pawn.getRoute().getRow());
            }
            pawns.addAll(newPawns);
            newPawns.clear();

            boolean notSolveble=true;
            for (Pawn pawn:pawns) {
                Route pawnRoute=pawn.getRoute();
                Contrato.Move[] options=getOptions(pawn);
                Contrato.Move lastMove = pawnRoute.route.get(pawnRoute.route.size()-1);
                switch (lastMove){
                    case NORT:lastMove= Contrato.Move.SOUTH;break;
                    case SOUTH:lastMove= Contrato.Move.NORT;break;
                    case EAST:lastMove= Contrato.Move.WEST;break;
                    case WEST:lastMove= Contrato.Move.EAST;break;
                }
                ArrayList<Contrato.Move> newOpions=new ArrayList<>();
                for(Contrato.Move option:options)
                    if(option!=lastMove)
                        newOpions.add(option);
                options=newOpions.toArray(new Contrato.Move[0]);
                if(options.length!=0)
                    notSolveble=false;
                if (isSolvedBy(pawn)) {
                    retPawn = pawn;
                    solvedFlag = true;
                    break;
                }
            }
            if(notSolveble)
                break;

        }
        System.out.println("Solved");
        return retPawn;
    }

}
