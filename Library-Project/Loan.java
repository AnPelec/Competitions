import java.io.*;
import java.util.*;
import java.math.*;
import java.text.*;
import java.util.Date.*;
import java.util.Calendar.*;
import java.util.GregorianCalendar.*;

public class Loan {
	
	/// class variables
	private int readerID;
	private int bookID;
	private Calendar dateOfLoan;
	private Calendar dateDueBack;
	
	/// constructor
	public Loan(int readerID, int bookID) {
		this.bookID = bookID;
		this.readerID = readerID;
		this.dateOfLoan = Calendar.getInstance();
		this.dateDueBack = Calendar.getInstance();
		this.dateDueBack.add(Calendar.DAY_OF_MONTH, 21);
	}
	
	/// print
	public int getReaderID() {
		return this.readerID;
	} 
	
	public int getBookID() {
		return this.bookID;
	}
	
	public boolean areEqual(Loan target) {
		if (this.readerID == target.getReaderID() && this.bookID == target.getBookID())
			return true;
		return false;
	}
	
	public boolean isOverDue() {
		Calendar now = Calendar.getInstance();
		if (this.dateDueBack.before(now))
			return true;
		return false;
	}
	
	public String printLoan() {
		SimpleDateFormat ft = new SimpleDateFormat ("dd-MM-yyyy");
		String temporaryDate = ft.format(dateOfLoan.getTime());
		String yoloDate = ft.format(dateDueBack.getTime());
		return "Reader with id: " + readerID + " is reading book with id: " + bookID + " since: " + temporaryDate + " " + yoloDate;
	}
}