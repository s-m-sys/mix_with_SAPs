**Folder - Training**

**Following explains the procedure to run the Training of the agent and data saved during the training**


Code for training an RL agent - PYTHON_C_MIXING_v1.ipynb

The initial position of particles is in 'ini_state_q1.csv' : column wise data - x position, y position, particle radius and particle type

'mixing.c' contains the C code for dynamics of the particle system and 'mixing.so' is the shared object file

Running the PYTHON_C_MIXING_v1.ipynb trains the agent to mix the system optimally.

The following folders are created: 

	logs - for tensorboard logs. saved under logs/PPO_0
	models - for saving the intermittent models. models are saved under models/PPO
	
	
	
**Folder - Test_run**

**Following Explains the procedure to run testing of a trained agent and data saved during the testing**


Code for training an RL agent - test_run.ipynb

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
