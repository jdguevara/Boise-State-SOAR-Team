import java.util.Scanner;
import java.io.*;

Class One_Byte{
    private Inputstream inputStream;
    private String path;

    public static void main(String[] args){
    	//args[0] = path to binary
	//args[1] = path to output csv
        path = args[0];
        One_Byte(path);
    }

    /*
        Constructor for One_Byte
        @param String fileName: The name of the encoded file
    */
    One_Byte(){
        System.out.println("Opening File...");

	try{
            InputStream inputStream = new FileInputStream(path);
	}catch(IOException e){
	    e.printStackTrace();
	}

	System.out.println("Starting Process...");
    }

    /*
    	Convert the file to an arraylist of data.
	@return The ArrayList of data points
    */
    private ArrayList<String> decodeFile(){
          System.out.println("Decoding...")

	  /*Code from online example*/
          long fileSize = new File(inputFile).length();
          byte[] allBytes = new byte[(int) fileSize];
          inputStream.read(allBytes);

	  //Convert data points to String and store in ArrayList dataPoints
          ArrayList<String> dataPoints = new ArrayList<String>();

          for(int i = 0; i < allBytes.length(); i++){
            dataPoints[i].add(allBytes[i].toString()); 
            System.out.println(dataPoints.get(i));
          }

          System.out.println("Done");

	  return dataPoints;

    }

    
    /*
    	Write the data in the ArrayList to a csv file
	@param data The ArrayList of data stored in binary file.
	@param csvPath The path to the csv file where the data will be stored
    */
    private void storeInCSV(ArrayList<String> data, String csvPath){
	
	//Open a csv to store the data in and format it.
	
	String dataLine = "";

	for(int i = 0; i < data.size(); i++){
		//Write to file
		if(i % 4 == 0){/*Print line to file*/
		else{/*add data point to end of dataLine with appropriately placed commas*/}
	}

	//Close file
    }

}
