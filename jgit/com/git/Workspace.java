package com.git;

import java.io.File;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.util.Collections;
import java.util.List;
import java.util.stream.Stream;
import java.util.stream.Collectors;

class Workspace {
    private String pathname;

    public Workspace(String pathname) {
        this.pathname = pathname;
    }

    public List<String> listFiles() {
        try (Stream<Path> walk = Files.walk(Paths.get(pathname))) {
             return walk.map(x -> x.toString())
                        .filter(f -> f.endsWith(".java"))
                        .collect(Collectors.toList());
        } catch (IOException e) {
            e.printStackTrace();
        }
        return Collections.emptyList();
    }

    public byte[] readFile(String path) throws IOException {
        return Files.readAllBytes(new File(path).toPath());
    }
}
