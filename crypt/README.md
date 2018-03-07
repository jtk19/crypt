Running OHLCV Formatter
-----------------------

You need the executable and the configuration file which you can get pre-built 
or from the build/ or the dist/ sub directories after building this repository.

- Executable: ohlcv_fmt
- Config file: crypt_config.txt

The Data:

Currently the program formats data from 2 feeds:
1. Bittrex Market History feed
2. bitcoin-historical-data feed

If you need to format data from other feeds, please provide them to the programmer
because different feeds come with different formats and the code need to be
changed to recognise the new feeds' formats.

Note: This OHLCV formatter provides daily bars. Both of the above feeds being
1 minute bars, the program aggregates all intra-day records for a single day to 
provide real and correct data for each day.   
Thus the Open is the Open for the first intra-day record.  
The Close is the Close of the last intra-day record.  
The High is the highest High of all the intra-day records.   
The the Low is the least Low of all intra-day records for the day.  
Volumes are aggregates of all the volums for the day.  
  
The program is written for UNIX operating systems and must be compiled and run on
any UNIX based distribution.

Download the pre-built executable for Fedora 26 (x86_64) from here:  
      https://www.dropbox.com/s/sd7r902qf53fduk/ohlcv_formatter.tar.gz?dl=0    

Then to unpack, run:  
$ gunzip ohlcv_formatter.tar.gz  
$ tar -xvf ohlcv_formatter.tar  
  
  
Steps for running:

1. Create a data directory to which the account running the program has read access to.  

2. Directly under this data directory, create one sub directory for each feed.  
Sub-directories named "zips/" and "bak/" are ignored. So, you can move any other
filed under one of these 2 directories.  There should be no other files or directories
directly under the data directory.  
  
Important:  
The name "Bittrex" must be in the name of the sub-directory for the Bittrex feed.  
The name "bitcoin" must be in the directory name of the sub-dir for the Bitcoin feed.  
Case doesn't matter; the feed name may be in the directory name in any case.  

3. Directly under each feed's sub-directory, copy each data CSV file. The CSV files
should be directly under the feed sub-directories. There should be no other sub-directories
to the CSV files.  
  
e.g:  
	/home/data/olhv_data/					## the data directory  
	.   |-> 'Bittrex Market History 8-3-2017'/		        ## the Bittrex feed sub-directory    
	.       |-> bittrex1.csv  
	.   |-> bitcoin-historical-data/				## the Bitcoin feed sub-directory  
	.       |-> Bitcoin1.csv  
	.   |-> zips/									## ignored  
	.   |-> bak/									## ignored  
	
4. Create a directory for the converted OHLCV csv files with write access for the program.
It is important that the program has write access to this directory.  

5. Into the config file, enter the data directory as the 'feeds_dir' and the directory
for the formatted destination CSV files as the 'write-dir'. e.g:  
  
$ cat config.txt  
feeds_dir=/home/data/crypt_data/  
write_dir=/home/data/crypt_ohlcv/  

6.  Put the executable and the config file in the same directory.
Make sure the program has executable rights and run it.  
  
$ ls ./bin  
ohlcv_fmt  
crypt_config.txt  
  
$ ./ohclv_fmt  
  
7.  The correctly converted OHLCV csv files will be written into the write_dir
named appropriately under the corresponding feed sub-directory.  
  
  
  
BUILDING Crypt Executables  
---------------------------  
  
* Make sure the C and C++ development tools are installed on your Linux machine, as root.  
   
 $ su -   
 \# yum update  
 \# yum groupinstall "Development Tools"  
  
* Check out our source code from Hithub.  
  
$ git clone https://github.com/jtk19/crypt.git  
  
* Change to the source code base directory and build with 'make'.  
  
$ cd crypt  
$ make clean  
$ make all  
$ make install  
  
* You will find the required executable and config file in the dist/ and build/ directories.  
  
* Follow the instructions in the section above to run the program.  
  





 





