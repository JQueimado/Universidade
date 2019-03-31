import javax.swing.*;
import java.io.*;
import java.util.ArrayList;

public class MazeIO{

    public static Maze read(File file) throws Exception{
            FileReader fileReader = new FileReader(file);
            BufferedReader bufReader = new BufferedReader(fileReader);

            String line = bufReader.readLine();
            ArrayList<String> fileInput = new ArrayList<>();
            while (line!=null){
                fileInput.add(line);
                line=bufReader.readLine();
            }

            bufReader.close();

            int xSize=fileInput.get(0).length();
            int ySize=fileInput.size();

            Contrato.MazeCell[][] outMazeTrace = new Contrato.MazeCell[xSize][ySize];

            boolean asStart=false;
            boolean asEnd=false;
            for (int y=0;y<ySize;y++){
                String s =fileInput.get(y);
                for(int x=0;x<xSize;x++)
                    switch (s.charAt(x)){

                        case 'S':
                            if (!asStart) {
                                outMazeTrace[x][y] = Contrato.MazeCell.START;
                                asStart=true;
                            }else
                                throw new Exception("Invalid maze: it has 2 Start Points");
                            break;

                        case 'E':
                            if (!asEnd) {
                                outMazeTrace[x][y] = Contrato.MazeCell.EXIT;
                                asEnd=true;
                            }else
                                throw new Exception("Invalid maze: it has 2 End Points");
                            break;

                        case 'W':outMazeTrace[x][y]= Contrato.MazeCell.WALL;break;
                        case '_':outMazeTrace[x][y]= Contrato.MazeCell.EMPTY;break;
                        default:throw new Exception("Invalid Char at:"+x+":"+xSize+","+y+":"+ySize+", from:"+s);
                    }

            }
            return new Maze(xSize,ySize,outMazeTrace,file.getName());
    }

    public static void write(Maze maze,String name) throws Exception{
        Contrato.MazeCell[][] cell =maze.maze;

        char[] toText =new char[(maze.numRows)*(maze.numCols+1)];
        int c=0;

        for (int y =0;y<maze.numRows;y++) {
            for (int x = 0;x<maze.numCols;x++)
                switch (cell[x][y]){
                    case START:toText[c]='S';c++;break;
                    case EMPTY:toText[c]='_';c++;break;
                    case EXIT:toText[c]='E';c++;break;
                    case WALL:toText[c]='W';c++;break;
                }
                toText[c]='\n';
                c++;
        }

        String fileDirect = "Mazes/"+name+".txt";

        File outFile = new File(fileDirect);
        if (!outFile.exists())
            outFile.createNewFile();
        FileOutputStream fileoutputStream = new FileOutputStream(outFile);
        DataOutputStream outputStream =new DataOutputStream(fileoutputStream);
        for (char ch:toText)
            outputStream.write(ch);
        outputStream.close();

        JOptionPane.showMessageDialog(null,"Saved in:"+fileDirect);
    }
}
