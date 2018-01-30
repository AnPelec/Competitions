import java.io.*;
import java.util.*;
import java.math.*;

public class Solution {
	
	public static BigInteger target, modulus;
	public static BigInteger zero = new BigInteger("0");
	public static BigInteger one = new BigInteger("1");
	public static BigInteger three = new BigInteger("3");
	public static BigInteger six = new BigInteger("6");
	
	public static void main(String[] args) {
		Long[] solution = new Long[2000000];
		BigInteger[] solution1 = new BigInteger[2000000];
		String line;
		double ok;
		Long targetLong, limit;
		Scanner sc = new Scanner(System.in);
		
		line = sc.next();
		targetLong = Long.parseLong(line);
		ok = targetLong.doubleValue();
		limit = Math.round(Math.pow(ok, 0.33333333D));
		target = new BigInteger(line);
		target = target.multiply(six);
		
		boolean isTheSame=false;
		int idx = 0;
		for (Long i=1L; i<=targetLong; i++) {
			BigInteger troll = ok(i);
			if ((BigInteger.valueOf(i).compareTo(troll) > 0)) break;
			if (modulus.compareTo(zero) == 0) {
				solution[idx] = i;
				solution1[idx] = troll;
				idx ++;
			}
		}
		
		if ((idx > 0) && (BigInteger.valueOf(solution[idx-1].intValue()).compareTo(solution1[idx-1]) == 0)) isTheSame = true;
		
		if (isTheSame) {
			int nIdx = 2*idx-1;
			System.out.println(nIdx);
		} else {
			int nIdx = 2*idx;
			System.out.println(nIdx);
		}
		
		for (int i=0; i<idx; i++) {
			System.out.println(solution[i] + " " + solution1[i]);
		}
		if (!isTheSame)
			System.out.println(solution1[idx-1] + " " + solution[idx-1]);
		for (int i=idx-2; i>=0; i--)
			System.out.println(solution1[i] + " " + solution[i]);
	}
	
	public static BigInteger ok(Long x) {
		BigInteger n = BigInteger.valueOf(x.intValue());
		BigInteger UHS = target;
		UHS = UHS.add(n.pow(3));
		UHS = UHS.subtract(n);
		
		BigInteger LHS = n;
		LHS = LHS.multiply(n.add(one));
		LHS = LHS.multiply(three);
		
		modulus = UHS.mod(LHS);
		
		return UHS.divide(LHS);
	}
}
