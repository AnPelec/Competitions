import java.io.*;
import java.util.*;
import java.math.*;

public class Book {
	
	/// class variables
	private int bookID;
	private String title;
	private String author;
	private boolean isFiction;
	
	/// constructor
	public Book(int bookID, String title, String author, boolean isFiction) {
		this.bookID = bookID;
		this.title = title;
		this.author = author;
		this.isFiction = isFiction;
	}
	
	/// print function
	public String getDetails() {
		return title + " " + author;
	}
	
	public String getTitle() {
		return this.title;
	}
	
	public int getID() {
		return this.bookID;
	}
}