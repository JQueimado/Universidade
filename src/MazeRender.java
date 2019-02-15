import javax.swing.*;
import java.awt.*;

public class MazeRender extends JPanel {

    public static final int MAZE_UNIT_SIZE =50;
    public static final int PAWN_UNIT_SIZE =40;

    public static final Color pawnColor =Color.BLACK;
    public static final Color emptyColor =Color.WHITE;
    public static final Color wallColor =Color.BLACK;
    public static final Color startColor =Color.RED;
    public static final Color exitColor =Color.GREEN;


    public MazeRender(Maze maze)throws Exception{
        if (maze==null)
            throw new Exception("Null maze");
        setVisible(true);
        setLayout(new GridLayout(maze.numRows,maze.numCols));
        Contrato.MazeCell[][] input = maze.maze;
        for (int y=0;y<maze.numRows;y++)
            for (int x=0;x<maze.numCols;x++){
                JPanel panel = new JPanel();
                Color color =null;
                switch (input[x][y]){
                    case EXIT:color =exitColor;break;
                    case WALL:color =wallColor;break;
                    case EMPTY:color=emptyColor;break;
                    case START:color=startColor;break;
                }
                panel.setBackground(color);
                add(panel);
            }

    }

    public static JPanel pawnRender(Pawn pawn){
        JPanel panel=new JPanel();
        panel.setOpaque(false);
        panel.setLayout(null);
        JPanel visualPawn=new JPanel();
        visualPawn.setBackground(pawnColor);
        int[] pawnRealCords =new int[2];
        pawnRealCords[0]=(pawn.getRoute().getCol()*MAZE_UNIT_SIZE)+((MAZE_UNIT_SIZE-PAWN_UNIT_SIZE)/2);
        pawnRealCords[1]=(pawn.getRoute().getRow()*MAZE_UNIT_SIZE)+((MAZE_UNIT_SIZE-PAWN_UNIT_SIZE)/2);
        visualPawn.setBounds(pawnRealCords[0],pawnRealCords[1],PAWN_UNIT_SIZE,PAWN_UNIT_SIZE);
        panel.add(visualPawn);
        return panel;
    }

}
