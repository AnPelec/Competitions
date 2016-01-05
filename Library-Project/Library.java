import java.io.*;
import java.util.*;
import java.math.*;

/**
	This class provides the following functionality
	-Create new member
	-Insert new book
	-Delete existing member
	-Delete existing book
	-Create loan
	-Delete loan
	-Query on members, books and loans
	-TODO: print
**/

public class Library {
	
	static int nextMemberID = 1;
	static int nextBookID = 1;
	public ArrayList < Member > members;
	public ArrayList < Book > books;
	public ArrayList < Loan > loans;
	
	public Library() {
		members = new ArrayList < Member >();
		books = new ArrayList < Book >();
		loans = new ArrayList < Loan>();
	}
	
	public void addNewMember(String firstName, String lastName, String telNumber) {
		int memberID = nextMemberID ++;
		Member newMember = new Member(memberID, firstName, lastName, telNumber);
		members.add(newMember);
	}
	
	public void addNewBook(String title, String author, boolean isFiction) {
		int bookID = nextBookID ++;
		Book newBook = new Book(bookID, title, author, isFiction);
		books.add(newBook);
	}
	
	public void deleteMember(int memberID) {
		for (Member now : members) {
			if (now.getID() == memberID) {
				members.remove(now);
			}
		}
	}
	
	public void deleteBook(int bookID) {
		for (Book now : books) {
			if (now.getID() == bookID) {
				books.remove(now);
			}
		}
	}
	
	public void printAllMembers() {
		for (Member now : members) {
			System.out.println(now.getDetails());
		}
	}
	
	public void printAllBooks() {
		for (Book now : books) {
			System.out.println(now.getDetails());
		}
	}
	
	public void printMember(int memberID) {
		for (Member now : members) {
			if (now.getID() == memberID) {
				System.out.println(now.getDetails());
			}
		}
	}
	
	public void printBook(int bookID) {
		for (Book now : books) {
			if (now.getID() == bookID) {
				System.out.println(now.getDetails());
			}
		}
	}
	
	public void findMember(String surname) {
		for (Member now : members) {
			if (now.getLastName().toLowerCase().contains(surname.toLowerCase())) {
				printMember(now.getID());
			}
		}
	}
	
	public void findBook(String title) {
		for (Book now : books) {
			if (now.getTitle().toLowerCase().contains(title.toLowerCase())) {
				printBook(now.getID());
			}
		}
	}
	
	public void addNewLoan(int memberID, int bookID) {
		Loan newLoan = new Loan(memberID, bookID);
		loans.add(newLoan);
	}
	
	public void deleteExistingLoan(int memberID, int bookID) {
		Loan target = new Loan(memberID, bookID);
		for (Loan now : loans) {
			if (now.areEqual(target)) {
				loans.remove(now);
			}
		}
	}
	
	public void printAllLoans() {
		for (Loan now : loans) {
			System.out.println(now.printLoan());
		}
	}
	
	public void printOverdueLoans() {
		boolean haveOverdue = false;
		for (Loan now : loans) {
			if (now.isOverDue()) {
				haveOverdue = true;
				System.out.println("User with id: " + now.getReaderID() + " has not returned yet the book with id : " + now.getBookID());
			}
		}
		
		if (!haveOverdue)
			System.out.println("No overdue loans!");
	}
	
	public static void main(String[] args) {
		Library example = new Library();
		
		example.addNewMember("Marios", "Kyriakou", "25524523");
		example.addNewMember("Gennady", "Korotkevich", "42342423");
		example.printAllMembers();
		example.addNewBook("Harry Potter", "J.K.Rowling", true);
		example.addNewBook("Competitive Programming 3", "Steven Halim", false);
		example.printAllBooks();
		example.addNewLoan(1, 1);
		example.addNewLoan(2, 2);
		example.printMember(2);
		example.printAllLoans();
		example.printOverdueLoans();
	}
}