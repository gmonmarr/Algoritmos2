/*

Pseudocódigo:

INTEGER PROCEDURE PAL(D, N); VALUE N; INTEGER N; INTEGER ARRAY D;
BEGIN INTEGER COUNT, ENP, MDP, BP; INTEGER ARRAY M(1:N - 1);
COMMENT N is the length of the input string. ENP (end pointer) is the cursor, MDP (middle
pointer) is the temporary center, and BP (beginning pointer) is the element of D that is the mirror
image of the cursor about the TC. All of these of course are indexes. The procedure PAL returns
either the index just beyond the initial even palindrome, if there is one, or else 0 if there is none;

ENP := 1; PAL := 0;
L1: ENP := ENP + 1; IF ENP = N + 1 THEN GOTO DONE;
MDP := BP := ENP – 1; COUNT := 0;
L2: WHILE D(ENP) = D(BP) DO
    BEGIN
    COUNT := COUNT + 1; ENP := ENP + 1; BP := BP – 1;
    IF BP = 0 THEN
        BEGIN
        PAL := ENP; GOTO DONE
        END;
    IF ENP = N + 1 THEN GOTO DONE
    END;
M(MDP) := COUNT; COMMENT Filling in # of symbols mirrored about MDP;
FOR F := 1 STEP 1 UNTIL COUNT DO
IF M(MDP – F) ≠ COUNT – F THEN
M(MDP + F) := MIN(COUNT – F, M(MDP – F)) ELSE
    BEGIN
    MDP := MDP + F; COUNT := COUNT – F;
    BP := MDP – COUNT; GOTO L2
    END;
GOTO L1;
DONE;
END
*/