import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Random;

public class Play {

    private static final int MOVE_UP=0;
    private static final int MOVE_DOWN=1;
    private static final int MOVE_LEFT=2;
    private static final int MOVE_RIHT=3;


    private static int moves=0;
    private static Pawn player;
    private static boolean downStroke=true;
    private static boolean allowInput=false;
    private static boolean playing=false;
    private static boolean created=false;

    private static void onClickAction(JPanel panel, Pawn pawn, Maze maze, Contrato.Move move){
        panel.setVisible(false);
        panel.removeAll();
        maze.move(pawn,move);
        System.out.println(pawn.getRoute().getCol()+":"+pawn.getRoute().getRow());
        JPanel player = MazeRender.pawnRender(pawn);
        player.setBounds(0,0,panel.getWidth(),panel.getHeight());
        panel.add(player);
        panel.setVisible(true);
        if (move!= Contrato.Move.NOOP)
            moves++;
        if (maze.isSolvedBy(pawn)) {
            allowInput=false;
            JOptionPane.showMessageDialog(null,"Congratulations: you solve this maze in "+moves+" moves");
            playing=false;
            downStroke=true;
        }
    }

    public static void playGame(Maze maze){

        try {
            JFrame frame = new JFrame(maze.name);
            int frameWidth = MazeRender.MAZE_UNIT_SIZE * maze.numCols;
            int frameHeight = MazeRender.MAZE_UNIT_SIZE * maze.numRows;
            frame.setSize(100 + frameWidth, 20 + frameHeight);
            Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
            frame.setLocation(dim.width / 2 - frame.getWidth() / 2, dim.height / 2 - frame.getHeight() / 2);
            frame.setLayout(null);
            frame.setResizable(false);
            frame.addWindowListener(new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e) {
                    allowInput=false;
                    super.windowClosing(e);
                }
            });

            JPanel scorePanel = new JPanel();
            scorePanel.setBorder(new TitledBorder("Score:"));
            scorePanel.setBounds(frameWidth + 20, 10, 75, 50);
            frame.add(scorePanel);

            JLabel movesLabel = new JLabel("Moves:" + moves);
            scorePanel.add(movesLabel);

            JPanel visualPawn = new JPanel();
            visualPawn.setBounds(10, 10, frameWidth, frameHeight);
            visualPawn.setOpaque(false);
            visualPawn.setLayout(null);
            visualPawn.setVisible(false);
            frame.add(visualPawn);

            MazeRender mazeRender = new MazeRender(maze);
            mazeRender.setBounds(10, 10, frameWidth, frameHeight);
            frame.add(mazeRender);


            JButton play = new JButton("PLAY");
            play.setBounds(frameWidth + 20, frame.getHeight() - 40, 70, 30);
            play.setEnabled(true);
            play.addActionListener(e -> {

                playing = true;
                play.setEnabled(false);

                moves = 0;

                int[] start = maze.getStartPosition();
                System.out.println("->" + start[0] + ":" + start[1]);
                player = new Pawn(start[0], start[1]);
                JPanel visualPlayer = MazeRender.pawnRender(player);
                visualPlayer.setBounds(0, 0, frameWidth, frameHeight);
                visualPawn.add(visualPlayer);
                visualPawn.setVisible(true);

                onClickAction(visualPawn, player, maze, Contrato.Move.NOOP);
                movesLabel.setText("Moves:" + moves);

                allowInput = true;

                if(!created)
                KeyboardFocusManager.getCurrentKeyboardFocusManager().addKeyEventDispatcher(e1 -> {
                    if (allowInput) {
                        created=true;
                        switch (e1.getKeyCode()) {
                            case KeyEvent.VK_W:
                            case KeyEvent.VK_UP:
                                if (downStroke) {
                                    onClickAction(visualPawn, player, maze, Contrato.Move.NORT);
                                    movesLabel.setText("Moves:" + moves);
                                }
                                downStroke=!downStroke;
                                break;

                            case KeyEvent.VK_S:
                            case KeyEvent.VK_DOWN:
                                if (downStroke) {
                                    onClickAction(visualPawn, player, maze, Contrato.Move.SOUTH);
                                    movesLabel.setText("Moves:" + moves);
                                }
                                downStroke=!downStroke;
                                break;

                            case KeyEvent.VK_A:
                            case KeyEvent.VK_LEFT:
                                if (downStroke) {
                                    onClickAction(visualPawn, player, maze, Contrato.Move.EAST);
                                    movesLabel.setText("Moves:" + moves);
                                }
                                downStroke=!downStroke;
                                break;

                            case KeyEvent.VK_D:
                            case KeyEvent.VK_RIGHT:
                                if (downStroke) {
                                    onClickAction(visualPawn, player, maze, Contrato.Move.WEST);
                                    movesLabel.setText("Moves:" + moves);
                                }
                                downStroke=!downStroke;
                                break;
                        }
                        if (!playing)
                            play.setEnabled(true);
                    }
                    return false;
                });
            });
            frame.add(play);

            frame.setVisible(true);
        }catch (Exception e){
            JOptionPane.showMessageDialog(null,"Error at Solve: "+e.getMessage());
            e.printStackTrace();
        }


    }

    private static boolean canMove(Maze maze,Pawn pawn,Contrato.Move move){
        Pawn testPawn =new Pawn(new Route(pawn.getRoute()));

        if (maze.canMove(testPawn,move))
            testPawn.move(move);
        else
            return false;

        int x=testPawn.getRoute().getCol();
        int y=testPawn.getRoute().getRow();

        if (maze.maze[x][y]== Contrato.MazeCell.WALL){

            if (maze.maze[x][y-1]!= Contrato.MazeCell.WALL)
                return false;

            if (maze.maze[x][y+1]!= Contrato.MazeCell.WALL)
                return false;

            if (maze.maze[x-1][y]!= Contrato.MazeCell.WALL)
                return false;

            if (maze.maze[x+1][y]!= Contrato.MazeCell.WALL)
                return false;
        }
        return true;

    }

    public static Maze create(String seed,String name)throws Exception{
        if(seed.length()!=6)
            throw new Exception("Invalid Seed");
        int xSize = Integer.parseInt(seed.substring(0,2));
        int ySize = Integer.parseInt(seed.substring(2,4));
        int difficulty= Integer.parseInt(seed.substring(4,6));

        Contrato.MazeCell[][] cell =new Contrato.MazeCell[xSize][ySize];
        Random random=new Random();
        Pawn aiCreator;
        Maze maze =new Maze(xSize,ySize,cell,name);

        for(int x=0;x<xSize;x++)
            for (int y=0;y<ySize;y++)
                cell[x][y]=Contrato.MazeCell.WALL;

        //setStart
        int xStart =random.nextInt(xSize);
        int yStart =random.nextInt(ySize);
        cell[xStart][yStart] = Contrato.MazeCell.START;

        //find main route
        aiCreator=new Pawn(xStart,yStart);
        int lastMove=-1;
        for (int c=0;c<difficulty;c++){
            int op = random.nextInt(4);
            int dist=0;
            Contrato.Move move = Contrato.Move.NOOP;

            System.out.println(lastMove);
            System.out.println("->"+c);
            if (op==lastMove)
                continue;

            switch (op){
                case MOVE_UP:
                    dist=aiCreator.getRoute().getRow();
                    lastMove=MOVE_DOWN;
                    move= Contrato.Move.NORT;
                    break;
                case MOVE_DOWN:
                    dist = maze.numRows-aiCreator.getRoute().getRow();
                    lastMove=MOVE_UP;
                    move = Contrato.Move.SOUTH;
                    break;
                case MOVE_LEFT:
                    dist=aiCreator.getRoute().getCol();
                    lastMove=MOVE_RIHT;
                    move= Contrato.Move.EAST;
                    break;
                case MOVE_RIHT:
                    dist=maze.numCols-aiCreator.getRoute().getCol();
                    lastMove=MOVE_LEFT;
                    move= Contrato.Move.WEST;
                    break;
            }

            dist=random.nextInt(dist+2);
            int c2=0;
            while (dist!=0){
                dist--;
                if (maze.canMove(aiCreator,move) && c!=difficulty) {
                    aiCreator.move(move);
                }else
                    break;
                c2++;
                if (c+c2==difficulty)
                    cell[aiCreator.getRoute().getCol()][aiCreator.getRoute().getRow()] = Contrato.MazeCell.EXIT;
                else
                    cell[aiCreator.getRoute().getCol()][aiCreator.getRoute().getRow()] = Contrato.MazeCell.EMPTY;
            }
            c+=c2;
        }

        return maze;
    }
}