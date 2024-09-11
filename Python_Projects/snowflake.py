from turtle import * 


def mainsnowflake(lengthsnowflake, finallength): 
    if finallength == 0:                
        forward(lengthsnowflake)        
        return                          

    lengthsnowflake /= 3.0              
    mainsnowflake(lengthsnowflake, finallength - 1)  
    left(60)                           
    mainsnowflake(lengthsnowflake, finallength - 1) 
    right(120)                        
    mainsnowflake(lengthsnowflake, finallength - 1) 
    left(60)                         
    mainsnowflake(lengthsnowflake, finallength - 1) 


if __name__ == "__main__":  
	right(90)            
	measurement = 300.0;          
	penup()                
	backward(measurement/2.0)    
	pendown()               
	for i in range(3):      
		mainsnowflake(measurement, 4)   
		right(120)         
		

mainloop() 