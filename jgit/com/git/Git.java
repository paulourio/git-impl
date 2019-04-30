package com.git;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.time.LocalDateTime;
import java.util.Scanner;

import com.git.Author;
import com.git.Blob;
import com.git.Commit;
import com.git.Entry;
import com.git.Tree;
import com.git.Workspace;

public class Git {

    public void command(String args[]) throws IOException {
        String command = args[0];

        if (command.equals("init")) {
            Path path = (FileSystems.getDefault()
                                    .getPath(args[1])
                                    .toAbsolutePath());
            Path git_path = path.resolve(".git").normalize();
            String[] dirnames = {"objects", "refs"};
            for (String dirname : dirnames) {
                File dir = git_path.resolve(dirname).toFile();
                Boolean created = dir.mkdirs();
                if (!created) {
                    System.err.println("fatal: could not create " + dir);
                    System.exit(1);
                }
            }
            System.out.println(
                "Initialized empty git repository in " + git_path
            );
        } else if (command.equals("commit")) {
            Path root_path = (FileSystems.getDefault()
                                         .getPath(".")
                                         .toAbsolutePath());
            Path git_path = root_path.resolve(".git").normalize();
            Path db_path = git_path.resolve("objects").normalize();

            Workspace ws = new Workspace(root_path.toString());
            Database database = new Database(db_path.toString());
            Tree tree = new Tree();
            for (String path : ws.listFiles()) {
                byte[] data = ws.readFile(path);
                Blob blob = new Blob(data);
                System.out.println(path);
                database.store(blob);
                tree.addEntry(new Entry(path, blob.getId()));
            }
            database.store(tree);

            String name = System.getenv("GIT_AUTHOR_NAME");
            String email = System.getenv("GIT_AUTHOR_EMAIL");
            Author author = new Author(name, email, LocalDateTime.now());
            String message = readMessage();
            Commit commit = new Commit(tree.getHex(), author, message);
            database.store(commit);

            try (PrintStream out =
                    new PrintStream(
                        new FileOutputStream(
                            git_path.resolve("HEAD").toString()))) {
                out.print(commit.getHex());
            }

            System.out.println("[(root-commit) " + commit.getHex() + " "
                               + message);
        } else {
            System.err.println("git: '" + command + "' is not a git command.");
            System.exit(1);
        }
    }

    private String readMessage() throws IOException {
        Scanner input = new Scanner(System.in);
        StringBuilder str = new StringBuilder();
        while (input.hasNextLine()){
            str.append(input.nextLine());
        }
        return str.toString();
    }
}
