package lab9;

import java.util.logging.Level;
import java.util.logging.Logger;

public class Lab9 {
	private static final int N = 5; // Number of philosophers
	private static final Semaphore[] forks = new Semaphore[N]; // Semaphores to represent the forks
	public static Philosophers[] philosophers = new Philosophers[N];
	
	enum phil_state { // States that the philosophers can have
	    THINKING,
	    HUNGRY,
	    EATING,
	}
	
	static int completedPhilosophers = 0;
	public static phil_state[] state = new phil_state[N]; // array to keep track of everyone's state

	private static Semaphore mutex = new Semaphore(1); // mutual exclusion
	
	private static int RIGHT(int i) {
	    return (i + 1) % N;
	}
	
	private static int LEFT(int i) {
	    return (i == 0) ? N - 1 : i - 1;
	}
	
	public static void main(String args[]){  
        for (int i = 0; i < N; i++) {
        	forks[i] = new Semaphore(0);
        	philosophers[i] = new Philosophers();
        }

        for(int i = 0; i < N; i++){
            philosophers[i].start();
        }
}
	
	
	
	public static class Philosophers extends Thread {
		private static int idNum = 0; // Helps assign philosopher ids
		private int id; // Instance Variables
		private boolean completed;
		
		public Philosophers(){
    	    this.id = idNum;
    	    idNum++;
    	    this.completed = false;
    	}
		
		private void test(int i) {
		    // if philosopher i is hungry and both neighbors are not eating then eat
		    if (state[i] == phil_state.HUNGRY &&
		        state[LEFT(i)] != phil_state.EATING &&
		        state[RIGHT(i)] != phil_state.EATING) {
		        state[i] = phil_state.EATING;
		        forks[i].up();
		    }
		}

		private void think() throws InterruptedException {
			Thread.sleep((long) (Math.random() * 1000));
		}

		private void getForks() throws InterruptedException {
			mutex.down(); // mutex entry
		    state[id] = phil_state.HUNGRY; // Current Phil is hungry
		    test(id); // try to get 2 forks
		    mutex.up(); // mutex exit
		    System.out.println("Philosopher " + (id+1) + " is waiting for Fork " + (RIGHT(id)+1));
		    forks[id].down(); // block if forks were not acquired
		    System.out.println("Fork " + (id+1) + " taken by Philosopher " + (id+1));
		    System.out.println("Fork " + (RIGHT(id)+1) + " taken by Philosopher " + (id+1));
		}

		private void eat() throws InterruptedException {
		    Thread.sleep((long) (Math.random() * 1000));
		}

		private void putForks() throws InterruptedException {
			mutex.down(); // mutex entry
		    state[id] = phil_state.THINKING; // Philosopher is back to thinking after finishing EATING
		    test(LEFT(id)); // test if left neighbor can now eat
		    test(RIGHT(id)); // test if right neighbor can now eat
		    mutex.up(); // mutex exit
		    completedPhilosophers++; // This Philosopher has now completed eating
		    this.completed = true;
		}
		
		/*
		 * returns the instance variable that shows whether or not the philosopher has finished eating
		 */
		private boolean isCompleted() {
			return this.completed;
		}
		
		/*
		 * Override of run() from the Thread class 
		 */
		@Override
    	public void run(){
    	    while (!isCompleted()) {// Checks if this philosopher is done eating
    	    	try {
        	        think();
					getForks();
					eat();
	    	        putForks();
				} catch (InterruptedException e) {
					Logger.getLogger(Lab9.class.getName()).log(Level.SEVERE, null, e);
					e.printStackTrace();
				}
    	    	
    	    	// After each Philosopher has finished eating prints the philosophers that have completed dinner and the number of
    	    	//	philosophers that have finished dinner.
    	    	for (int i = 0; i < N; i++) {
        	        if (philosophers[i].isCompleted()) {
        	            System.out.println("Philosopher " + (philosophers[i].id+1) + " completed his dinner");
        	        }
        	    }
    	        System.out.println("Philosopher " + (id+1) + " released fork " + (id + 1) + " and " + (RIGHT(id)+1));
        	    System.out.println("Till now num of philosophers completed dinner are " + completedPhilosophers);
    	    } 	    
    	}
	}
}
