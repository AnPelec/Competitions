import java.io.*;
import java.util.*;
import java.math.*;

/**
	Class for Library Members
**/


public class Member {
	
	/// class variables
	private int memberID;
	private String firstName;
	private String lastName;
	private String phoneNumber;
	
	/// constructors
	public Member(int memberID, String firstName, String lastName, String phoneNumber) {
		this.firstName = firstName;
		this.lastName = lastName;
		this.phoneNumber = phoneNumber;
		this.memberID = memberID;
	}
	
	/// print function
	public String getDetails() {
		return firstName + " " + lastName + " " + phoneNumber;
	}
	
	public int getID() {
		return this.memberID;
	}
	
	public String getLastName() {
		return this.lastName;
	}
}