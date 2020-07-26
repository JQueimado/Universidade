import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;

public class WindowMng {

    public static void showSolveMazeWindow(Maze maze)throws Exception{
        JFrame frame =new JFrame(maze.name);
        int frameWidth =MazeRender.MAZE_UNIT_SIZE*maze.numCols;
        int frameHeight =MazeRender.MAZE_UNIT_SIZE*maze.numRows;
        frame.setSize(20+frameWidth,60+frameHeight);
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        frame.setLocation(dim.width/2-frame.getWidth()/2,dim.height/2-frame.getHeight()/2);
        frame.setLayout(null);
        frame.setResizable(false);

        JPanel pawns =new JPanel();
        pawns.setBounds(10,10,frameWidth,frameHeight);
        pawns.setOpaque(false);
        pawns.setLayout(null);
        pawns.setVisible(false);
        frame.add(pawns);

        int[] start =maze.getStartPosition();
        Pawn aiPawn = new Pawn(start[0],start[1]);
        JPanel pawnGraphics =MazeRender.pawnRender(aiPawn);
        pawnGraphics.setBounds(0,0,frameWidth,frameHeight);
        pawns.add(pawnGraphics);

        Pawn solvePawn =maze.solve();
        if (solvePawn==null)
            throw new Exception("Mase is impocible");
        for (Contrato.Move move :solvePawn.getRoute().route){
            maze.move(aiPawn,move);
            JPanel visualPawn =MazeRender.pawnRender(aiPawn);
            visualPawn.setBounds(0,0,frameWidth,frameHeight);
            System.out.println(aiPawn.getRoute().getCol()+":"+aiPawn.getRoute().getRow());
            pawns.add(visualPawn);
        }

        System.out.println("Done");

        MazeRender mazeRender=new MazeRender(maze);
        mazeRender.setBounds(10,10,frameWidth,frameHeight);
        frame.add(mazeRender);

        JButton solve =new JButton("Solve");
        solve.setBounds(10,frame.getHeight()-35,100,30);
        solve.addActionListener(e -> {
            if (pawns.isVisible())
                pawns.setVisible(false);
            else
                pawns.setVisible(true);
        });
        frame.add(solve);

        JButton back = new JButton("Back");
        back.setBounds(frame.getWidth()-110,frame.getHeight()-35,100,30);
        back.addActionListener(e -> {
            frame.dispose();
        });
        frame.add(back);

        frame.setVisible(true);
    }

    public static void showPlayWindow (){
        JFrame menu =new JFrame("Game Menu");
        menu.setSize(300,150);
        menu.setLayout(null);
        menu.setLocationRelativeTo(null);
        menu.setResizable(false);

        JButton playFromAFileButton =new JButton("Play from a file");
        playFromAFileButton.setBounds(menu.getWidth()/2-100,10,200,25);
        playFromAFileButton.addActionListener(e -> {
            try {
                JFileChooser chooser = new JFileChooser();
                chooser.setFileFilter(new FileNameExtensionFilter("TEXT FILES", "txt", "text"));
                chooser.showOpenDialog(null);
                Maze maze=MazeIO.read(chooser.getSelectedFile());
                if(maze.solve()!=null)
                    Play.playGame(maze);
                else
                    throw new Exception("Mase is impocible");
            }catch (Exception e1){
                JOptionPane.showMessageDialog(null,"Error at Play: "+e1.getMessage());
                e1.printStackTrace();
            }
        });
        menu.add(playFromAFileButton);

        menu.setVisible(true);
    }


}
