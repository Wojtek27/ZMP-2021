#define Speed 100
#define HighSpeed 200
#define PathLength 50

Begin_Parallel_Actions
    Move Podstawa Speed PathLength
End_Parallel_Actions

Begin_Parallel_Actions
    Rotate Podstawa 45 Z 90
End_Parallel_Actions

Begin_Parallel_Actions
    Pause 1000
End_Parallel_Actions

Begin_Parallel_Actions
    Move Podstawa HighSpeed PathLength
End_Parallel_Actions