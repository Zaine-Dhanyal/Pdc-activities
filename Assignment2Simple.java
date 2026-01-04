import java.util.Random;

class SumThread extends Thread {
    private int[] arr;
    private int start, end;
    private long sum;

    public SumThread(int[] arr, int start, int end) {
        this.arr = arr;
        this.start = start;
        this.end = end;
        this.sum = 0;
    }

    public void run() {
        for (int i = start; i < end; i++) {
            sum += arr[i];
        }
    }

    public long getSum() {
        return sum;
    }
}

public class Assignment2Simple {
    public static void main(String[] args) throws InterruptedException {
        int SIZE = 10000;
        int[] arr = new int[SIZE];
        Random rand = new Random();

        for (int i = 0; i < SIZE; i++) {
            arr[i] = rand.nextInt(100);
        }

        long startSerial = System.nanoTime();
        long serialSum = 0;
        for (int i = 0; i < SIZE; i++) {
            serialSum += arr[i];
        }
        long endSerial = System.nanoTime();
        double timeSerial = (endSerial - startSerial) / 1e6;

        System.out.println("Serial Sum: " + serialSum);
        System.out.println("Serial Time: " + timeSerial + " ms");
        System.out.println("----------------------------------------");

        int[] threadCounts = {4, 5, 10};

        for (int numThreads : threadCounts) {
            SumThread[] threads = new SumThread[numThreads];
            int chunkSize = SIZE / numThreads;
            long startParallel = System.nanoTime();

            for (int t = 0; t < numThreads; t++) {
                int start = t * chunkSize;
                int end = (t == numThreads - 1) ? SIZE : start + chunkSize;
                threads[t] = new SumThread(arr, start, end);
                threads[t].start();
            }

            long parallelSum = 0;
            for (int t = 0; t < numThreads; t++) {
                threads[t].join();
                parallelSum += threads[t].getSum();
            }

            long endParallel = System.nanoTime();
            double timeParallel = (endParallel - startParallel) / 1e6;
            double speedup = timeSerial / timeParallel;

            System.out.println(numThreads + " Threads Sum: " + parallelSum);
            System.out.println(numThreads + " Threads Time: " + timeParallel + " ms");
            System.out.println("Speedup: " + speedup);
            System.out.println("----------------------------------------");
        }
    }
}
