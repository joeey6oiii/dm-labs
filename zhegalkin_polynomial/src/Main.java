import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int numberOfVariables;
        int[] column;
        
        try (Scanner scanner = new Scanner(System.in)) {
            numberOfVariables = Integer.parseInt(scanner.nextLine());
            column = new int[(int) Math.pow(2, numberOfVariables)];

            for(int i = 0; i < Math.pow(2, numberOfVariables); i++){
                String variableValues = "";
                while(variableValues.length() != numberOfVariables + 1){
                    variableValues = scanner.nextLine().replace(" ", "");
                    for(int j = 0; j < variableValues.length(); j++){
                        column[i] = variableValues.charAt(j) - '0';
                    }
                }
            }
        }

        ArrayList<Integer> zhegalkinPolynomial = new ArrayList<>();
        zhegalkinPolynomial.add(column[0]);

        int lastElement = column.length;
        while(zhegalkinPolynomial.size() != (int) Math.pow(2, numberOfVariables)){
            for(int i = 0; i < column.length - 1; i++){
                column[i] = (column[i] + column[i + 1]) % 2;
            }

            lastElement--;
            column[lastElement] = 0;

            zhegalkinPolynomial.add(column[0]);
        }

        StringBuilder result = new StringBuilder();
        for(int i = 0; i < zhegalkinPolynomial.size(); i++){
            if(zhegalkinPolynomial.get(i) == 1){
                result.append(" + ");

                if(i == 0){
                    result.append("1");
                } else {
                    for(int j = numberOfVariables; j >= 0; j--){
                        if((i & (1 << j)) != 0){
                            result.append((char)('a' + numberOfVariables - j - 1));
                        }
                    }
                }
            }
        }
        
        System.out.println(result.length() > 0 ? result.substring(3) : "0");
    }
}