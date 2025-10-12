**Folder - Training**

**Following explains the procedure to run the Training of the agent and data saved during the training**


Code for training an RL agent - PYTHON_C_MIXING_v1.ipynb - run the entire code in jupyter notebook all at once.

The initial position of particles is in 'ini_state_q1.csv' : column wise data - x position, y position, particle radius and particle type

'mixing.c' contains the C code for dynamics of the particle system and 'mixing.so' is the shared object file

Running the PYTHON_C_MIXING_v1.ipynb trains the agent to mix the system optimally.

The following folders are created: 

	logs - for tensorboard logs. saved under logs/PPO_0
	models - for saving the intermittent models. models are saved under models/PPO
	
	
	
**Folder - Test_run**

**Following Explains the procedure to run testing of a trained agent and data saved during the testing**


Code for training an RL agent - test_run.ipynb - run the entire code in jupyter notebook all at once.

The initial position of particles is in 'ini_state_q1.csv' : column wise data - x position, y position, particle radius and particle type

'mixing.c' contains the C code for dynamics of the particle system and 'mixing.so' is the shared object file

Running the test_run.ipynb runs a case using a trained agent (example given is a trained model named 250.zip) to mix the system.

The following folders are created: 

	     pos_data - contains the position of the particle for test run. There can be multiple test episodes while running 'test_run.ipynb'. 
		              Data is stored under 'pos_data/RL_particle_data_{episode}/state_{time}.csv', where episode has to be replaced wuith episode number, and time with corresponsing time.
		              Each file saved in 'pos_data/RL_particle_data_{episode}' has data in column wise order as x position, y position, particle radius, angle of propulsion, particle type
		              In the folder pos_data, RL_particle_data_0 stores data while checking the environment.
		              To get the data during testing for complete episode using the trained model, look in to 'RL_particle_data_1' to 'RL_particle_data_50' for 50 test episodes.
		   
The file 'MI_vs_Time.csv' gives mixing index (MI) obtained at defined time over multiple test episodes. First column stands for time and rest all columns gives the MI for each test episode against the time.

***Folder - Figures_and_data***

All the files in the folder are written in Jupyter Notebook
ini_state_q1.csv as well as ini_state_q1.txt contains x,y data for the particles at time, t=0 (x data available in first column and y data available in 2nd column)

**Figure_1_a_initial_distribution:**

Open the file imageGen.ipynb and run all the cells together
Needs ini_state_q1.csv as the source file to create the image


**Figure_3_a:**
Open the file imageGen.ipynb and run all the files together
Needs the source files as t_500.txt, t_5000.txt, t_15000.txt, t_50000.txt to create the images

**Figure_3_b:**
Open the file act_particle_loci_cmap_from_active_data.ipynb and run all the cells together
Needs two files for running: ini_state_q1.txt, RT_active_data.csv. RT_active_data.csv contains the x,y positions of the active particles at definite time intervals, which is also given in the file

**Figure_4:**
Figure_4_a_traj:
Open the file trajectory_plots.ipynb and run all the cells together
Needs ini_state_q1.csv and test files trajectory_11.txt, trajectory_42.txt, trajectory_121.txt
Figure_4_b_prob_occurance:
Open the file heat_map_from_data.ipynb and run all the cells together
Need the files part_occur_data_RT1.csv and part_occur_data_RT2.csv

**Figure_5:**
For Trained:
Run imageGen.ipynb along with files state_500.csv, state_5000.csv, state_15000.csv, state_50000.csv in the corresponding folder
For non-Trained:
Run imageGen.ipynb along with files state_500.csv, state_5000.csv, state_15000.csv, state_50000.csv in the corresponding folder

**Figure_6:**
Fig_6_a_i:
Open the file act_particle_lovi_cmap_from_act_data.ipynb and run all the cells together along with the files active_data_NTSAP.csv and ini_state_q1.txt
Fig_6_a_ii:
Open the file act_particle_lovi_cmap_from_act_data.ipynb and run all the cells together along with the files active_data_TSAP.csv and ini_state_q1.txt
Fig_6_b:
Open the file traj_active_from_data.ipynb and run all the cells together along with ini_state_q1.txt and trajectory_data.csv
Fig_6_c_inset:
Open the file consolidated_mean_curves_RTP.ipynb and run all the cells together along with the folders tau_5 till tau_40 in the folder
Fig_6_c_main:
Open the file plotting_graphs_with_band.ipynb along with the files MI_vs_Time_non_opt.csv, MI_vs_Time_opt.csv and ini_state_q1.txt

**Figure_7:**
This is a matlab file - dist_fit.m. Run along with neigh_listing which has data about neighbour count of particles at definite time for an optimal case and non optimal case. For selecting the distribution and fit for a given time put corresponding value for T at the matlab code. for the attached file, T=50000

**Figure_8:**
Fig_8_a:
Open the file quiver_colour_plots.ipynb along with the files ini_state_q1.txt, trajectory_11.txt, trajectory_42.txt and trajectory_121.txt
Fig_8_b:
Open the file quiver_colour_plots.ipynb alng with the files ini_state_q1.txt and trajectory_9.txt
Fig_8_c:
Open file Ridge_plot_from_data.ipynb along with the folder ridge_data - contains data on angular velocity of passive particles

**Figure_9:**
Open the file Consolidated_figs_delta_fixed_gamma_varying.ipynb along with the file TSAP_MI_data.csv

