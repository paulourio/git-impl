import java.io.File;
import java.nio.file.FileSystems;
import java.nio.file.Path;

class GitInterface {

    public static void main(String args[]) {
        String command = args[0];

        if (command.equals("init")) {
            Path path = (FileSystems.getDefault()
                                    .getPath(args[1])
                                    .toAbsolutePath());
            Path git_path = path.resolve(".git").normalize();
            String[] dirnames = {"objects", "refs"};
            for (String dirname : dirnames) {
                File dir = git_path.resolve(dirname).toFile();
                dir.mkdirs();
            }
            System.out.println(
                "Initialized empty git repository in " + git_path
            );
        } else {
            System.err.println("git: '" + command + "' is not a git command.");
            System.exit(1);
        }
    }
}
