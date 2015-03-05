
import java.util.Arrays;

/*
 * Compilations:
 * javac -g MyStack.java
 * java MyStack
 */
public class MyStack {

    static class ArrayStack<E> {

        private int size = 0;
        private static final int DEFAULT_COMPACITY = 10;
        private int factor;
        private Object elements[];

        public ArrayStack(int factor) {
            this.factor = factor;
            elements = new Object[DEFAULT_COMPACITY];
        }

        public ArrayStack() {
            this(2);
        }

        public void push(E e) {
            if (size == elements.length) {
                ensureCompacity();
            }

            elements[size++] = e;
        }

        public E pop() {
            E e = (E) elements[--size];
            elements[size] = null;

            return e;
        }

        private void ensureCompacity() {
            int newSize = elements.length * factor;
            elements = Arrays.copyOf(elements, newSize);
        }

    }

    public static void main(String args[]) {
        ArrayStack<Integer> stack = new ArrayStack<Integer>();
        stack.push(1);
        stack.push(2);
        stack.push(3);
        stack.push(3);
        stack.push(4);
        System.out.println(4 == stack.pop());
        System.out.println(3 == stack.pop());
        System.out.println(3 == stack.pop());
        System.out.println(2 == stack.pop());
        System.out.println(1 == stack.pop());
    }
}