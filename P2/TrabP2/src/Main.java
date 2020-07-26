import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;


public class Main {

    private static Maze maze;

    public static void main(String[] a){
            JFrame frame =new JFrame("MainMenu:");
            frame.setLayout(null);
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setResizable(false);
            frame.setLocationRelativeTo(null);
            frame.setSize(150,190);
            Dimension dim =Toolkit.getDefaultToolkit().getScreenSize();
            frame.setLocation(dim.width/2-frame.getWidth()/2,dim.height/2-frame.getHeight()/2);
            JButton solve,play,create;

            solve=new JButton("Solve");
            solve.setBounds(frame.getWidth()/2-50,10,100,50);
            solve.addActionListener(e -> {
                try {
                    JFileChooser chooser = new JFileChooser();
                    chooser.setFileFilter(new FileNameExtensionFilter("TEXT FILES", "txt", "text"));
                    chooser.showOpenDialog(null);
                    WindowMng.showSolveMazeWindow(MazeIO.read(chooser.getSelectedFile()));
                }catch (Exception e1){
                    JOptionPane.showMessageDialog(null,"Error at Solve: "+e1.getMessage());
                    e1.printStackTrace();
                }
            });

            play=new JButton("Play");
            play.setBounds(frame.getWidth()/2-50,70,100,50);
            play.addActionListener(e -> {
                    WindowMng.showPlayWindow();
            });

            create=new JButton("Create");
            create.setBounds(frame.getWidth()/2-50,130,100,50);
            create.addActionListener(e -> {
                try {
                    String seed ="101005";
                    String name="test";
                    maze=Play.create(seed,name);
                    JFrame frame1 =new JFrame(maze.name);
                    int frameWidth =MazeRender.MAZE_UNIT_SIZE*maze.numCols;
                    int frameHeight =MazeRender.MAZE_UNIT_SIZE*maze.numRows;
                    frame1.setSize(20+frameWidth,55+frameHeight);
                    Dimension dim1 = Toolkit.getDefaultToolkit().getScreenSize();
                    frame1.setLocation(dim1.width/2-frame1.getWidth()/2,dim1.height/2-frame1.getHeight()/2);
                    frame1.setLayout(null);
                    frame1.setResizable(false);

                    JPanel mazeRenderPanel=new JPanel();
                    mazeRenderPanel.setBounds(10,10,frameWidth,frameHeight);
                    mazeRenderPanel.setLayout(null);

                    MazeRender mazeRender=new MazeRender(maze);
                    mazeRender.setBounds(0,0,mazeRenderPanel.getWidth(),mazeRenderPanel.getHeight());
                    mazeRenderPanel.add(mazeRender);

                    frame1.add(mazeRenderPanel);

                    JButton save = new JButton("Save");
                    save.setBounds(10,frameHeight+20,100,25);
                    save.addActionListener(e12 -> {
                        String fileName= JOptionPane.showInputDialog("Nome do fixeiro:");
                        try {
                            MazeIO.write(maze, fileName);
                        }catch (Exception e1){
                            JOptionPane.showMessageDialog(null,"Storing ERROR: "+e1.getMessage());
                            e1.printStackTrace();
                        }
                    });
                    frame1.add(save);

                    JButton createOther = new JButton("Create");
                    createOther.setBounds((frame1.getWidth()/2)-50,frameHeight+20,100,25);
                    createOther.addActionListener(e13 -> {
                        try {
                            maze = Play.create(seed, name);
                            mazeRenderPanel.setVisible(false);
                            mazeRenderPanel.removeAll();
                            MazeRender mazeRender1 =new MazeRender(maze);
                            mazeRender1.setBounds(0,0,mazeRenderPanel.getWidth(),mazeRenderPanel.getHeight());
                            mazeRenderPanel.add(mazeRender1);
                            mazeRenderPanel.setVisible(true);
                        }catch (Exception e1){
                            JOptionPane.showMessageDialog(null,"Error at Create: "+e1.getMessage());
                            e1.printStackTrace();
                        }

                    });

                    frame1.add(createOther);

                    JButton back =new JButton("Back");
                    back.setBounds(frame1.getWidth()-110,frameHeight+20,100,25);
                    back.addActionListener(e14 -> {
                        frame1.dispose();
                    });

                    frame1.add(back);

                    frame1.setVisible(true);

                }catch (Exception e1){
                    JOptionPane.showMessageDialog(null,"Error at Create: "+e1.getMessage());
                    e1.printStackTrace();
                }
            });

            frame.add(solve);
            frame.add(play);
            frame.add(create);
            frame.setVisible(true);
    }
}
