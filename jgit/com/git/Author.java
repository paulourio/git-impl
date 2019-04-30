package com.git;

import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.time.OffsetDateTime;

class Author {
    private String name;
    private String email;
    private LocalDateTime time;

    Author(String name, String email, LocalDateTime time) {
        this.name = name;
        this.email = email;
        this.time = time;
    }

    public String toString() {
        ZoneOffset offset = OffsetDateTime.now().getOffset();
        Long ltime = time.toEpochSecond(offset);
        return String.format("%s <%s> %d %s", name, email, ltime,
                             offset.toString().replace(":", ""));
    }
}
