Author: 	Mark van der Broek
Version:	0.1

--------------------------------------------------------------------------------
Overview:	In this file you can find the progress of the project.
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
CLASSES
	
LShaped:
	Additions:
		- Upgrade importance of branching the OR variables (x) first.
		- Solve the problem iteratively by adding cuts using callback function.

	Bugs:
		- 	Optimality cuts are not correct yet. Reason unknown. Maybe T matrix. 
			However this seems rather unlikely
		- 	Eta value calculate by solving master problem is unrealistic 
			(zero in the beginning)

MasterProblem:
	Additions:
		-	

	Bugs:
		-	Seems to work perfect.

RecourseModel:
	Additions:
		-	

	Bugs:
		-	Seems to work perfect.

SAAMethod:
	Additions:
		-	Solve problem for integer second-stage variables. This is however an 
			unfair comparison w.r.t. L-shaped.

	Bugs:
		-	Seems to work perfect.

SubProblem:
	Additions:
		-	

	Bugs:
		-	Seems to work perfect.
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
GENERAL IDEAS

-	Look at the effect of larger values for eps1 and eps2 on the objective value,
	size of the overtime, and opened ORs (these are all related of course).
-	Compare the speed of the two solution methods for different experimental
	set-ups.
-	Consider value of the stochastic solution by copmuting at mean. Slightly different
        since we consider the minmax problem. However, I constructed an
        equivalent formulation that does not have the maximization anymore, but a
        reference category.
    
--------------------------------------------------------------------------------


