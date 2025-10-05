#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* mix_state(double* state, double* d_theta, int rows, int cols, double P_rad, double D_rad, int N_wall, int N_passive, int N_active, double delta_t) 
{ // receive the state with x,y,r,part
    // Create new_arr_2d and perform operations on the array
//    printf("C function call \n");
    double** new_state = (double**)malloc(rows*sizeof(double*));
    for (int i = 0; i < rows; i++) {
        new_state[i] = (double*)malloc(cols*sizeof(double));
        for (int j = 0; j < cols; j++) {
        	new_state[i][j] = state[i * cols + j];
        }
    }            	
        
    	const double DOM_RAD = D_rad;
	const double RAD = P_rad;
	const double vel = 1.0;
	
	double* posx = (double*)malloc(sizeof(double)*rows);
	double* posy = (double*)malloc(sizeof(double)*rows);
	double* speed = (double*)malloc(sizeof(double)*rows);
	double* rad = (double*)malloc(sizeof(double)*rows);
	int* part_type = (int*)malloc(sizeof(int)*rows);

	const double mu_inv = 1.0;	// Inverse of mobility
	const double k = 10.0;	// Spring constant k
	double dt = 0.01;	// Time step
	int iter = round(delta_t/dt);
	double MIN_SEP;
	
	for(int i=0;i<rows;i++){
	   posx[i] = new_state[i][0];
   	   posy[i] = new_state[i][1];
   	   rad[i] = new_state[i][2];
   	   part_type[i] = (int)(new_state[i][3]);
   	   if(part_type[i] == 1)	speed[i] = vel;
   	   else speed[i] = 0.0;
   	}

        //********************************************
	char time_data[50];

	int N_total = N_active+N_wall+N_passive;

	double l_cell = 4.0*RAD;
	double L[2][2];

	L[0][0] = posx[0];
	L[0][1] = posx[0];
	L[1][0] = posy[0];
	L[1][1] = posy[0];

	for(int i=1;i<rows;i++){
		if(posx[i] < L[0][0])	L[0][0] = posx[i];
		if(posx[i] > L[0][1])	L[0][1] = posx[i];

		if(posy[i] < L[1][0])	L[1][0] = posy[i];
		if(posy[i] > L[1][1])	L[1][1] = posy[i];
	}

	L[0][0] -= l_cell;
	L[0][1] += l_cell;
	L[1][0] -= l_cell;
	L[1][1] += l_cell;

	int Nc_x = ceil((L[0][1]-L[0][0])/l_cell);	// No. of cells in neighbour list in x-direction
	int Nc_y = ceil((L[1][1]-L[1][0])/l_cell);	// No. of cells in neighbour list in y-direction
	int Nc_t = Nc_x*Nc_y;	// Total no. of cells  

	int* head = (int*)malloc(Nc_t*sizeof(int));
	int* list = (int*)malloc(N_total*sizeof(int));

	double* prev_posx = (double*)malloc(N_total*sizeof(double));
	double* prev_posy = (double*)malloc(N_total*sizeof(double));
	
	double dx, dy, distance;
	
		
	// Neighbour list implementation starts here
	// iter=delta_t/dt times the process is repeated and positions are updated each time
	for(int i_count=0;i_count<iter;i_count++)
	{
		for(short unsigned i=0; i<Nc_t; i++) head[i] = -1; //Assigning the values to head cell as -1

		int cell_ix, cell_iy, cell_n;
		for (short unsigned i=0; i<N_total; i++) // Maping the particles to 'list' and 'head' arrays
		{
			prev_posx[i] = posx[i];
			prev_posy[i] = posy[i];

			cell_ix = (int)((prev_posx[i]-L[0][0])/l_cell);
			cell_iy = (int)((prev_posy[i]-L[1][0])/l_cell);		// Putting agent into respective xcell and ycell

			cell_n = cell_ix*Nc_y + cell_iy;	// Cell number calculated vertically
			list[i] = head[cell_n];
			head[cell_n] = i;
		}		
	
		int neigh_cell[2], neigh_cell_n, iat, jat;
		for (int i=0; i<Nc_x; i++)
		{
			for (int j=0; j<Nc_y; j++)
			{
				cell_n = i*Nc_y + j; 
				    
				iat = head[cell_n];  
				
				while (iat != -1) // outer layer cells are skipped
				{
					double force_x=0.0;
					double force_y=0.0;
					for (neigh_cell[0] = i-1; neigh_cell[0] <= i+1; (neigh_cell[0])++) // i will alyays be an inside cell
					{
						for (neigh_cell[1] = j-1; neigh_cell[1] <= j+1; (neigh_cell[1])++) 
						{ 
							neigh_cell_n = neigh_cell[0]*Nc_y + neigh_cell[1];
								
							jat = head[neigh_cell_n];	
							while (jat != -1)
							{
							  	if(iat != jat && part_type[iat]!=0)
							  	// No need to calculate force for wall particles 
							  	{
									//distance calculation of neighboring particles
									dx = prev_posx[jat] - prev_posx[iat]; 
									dy = prev_posy[jat] - prev_posy[iat];

									distance = sqrt(dx*dx + dy*dy);
									MIN_SEP = rad[iat]+rad[jat];

									if (distance > 0 && distance < MIN_SEP) 
					            			{	
										force_x += (distance-MIN_SEP)*dx/distance;
										force_y += (distance-MIN_SEP)*dy/distance;
									}
								}
								jat = list[jat];
							}
						}
					}
					if(part_type[iat]!=0) // updating the position of particles
					{
						posx[iat] += (force_x*mu_inv*k + speed[iat]*cos(d_theta[iat]))*dt;
						posy[iat] += (force_y*mu_inv*k + speed[iat]*sin(d_theta[iat]))*dt;	
					}
					iat = list[iat];	
				}
		 	}
		}

	
	}
	
	
	// Copy the modified data back to 2D array
	for(int i=0;i<rows;i++){
	   new_state[i][0] = posx[i];
   	   new_state[i][1] = posy[i];
   	   }
   	     	      
   	double* up_state = (double*)malloc((rows * cols)*sizeof(double));
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
	    	    up_state[i * cols + j] =  new_state[i][j];

	//*******************************************
	
	free(posx);
	free(posy);
	free(rad);
	free(speed);
	free(part_type);
	free(prev_posx);
	free(prev_posy);
	free(head);
	free(list);


    for (int i = 0; i < rows; i++) 
    	free(new_state[i]); // Deallocate memory for each row
    free(new_state); // Deallocate memory for the array of row pointers
        
    return up_state;
}


void free_array(double* array) {
    free(array);
}
