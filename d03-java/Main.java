import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class Main {
  public static void main(String[] args) throws IOException {
    List<String> input = Files.readAllLines(Paths.get("input.txt"));

    final int height = input.size();
    final int width = input.get(0).length();
    int y = 0;
    int x = 0;
    int result = 0;
    while (y < height) {
      int y1 = y + 1;
      int x1 = (x + 3) % width;

      if (y1 < height) {
        if (input.get(y1).charAt(x1) == '#') {
          result += 1;
        }
      }

      y = y1;
      x = x1;
    }

    System.out.println(result);
  }
}
