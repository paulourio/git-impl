import java.io.IOException;

import com.git.Git;

public class GitInterface {

    public static void main(String args[]) {
        Git git = new Git();
        try {
            git.command(args);
        } catch (IOException err) {
            err.printStackTrace();
            System.exit(1);
        }
    }
}
