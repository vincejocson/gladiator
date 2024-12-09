/******************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and
applying the concepts learned. I have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and debugged by my own efforts. I
further certify that I have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons.
Vince Miguel S. Jocson, DLSU ID# 12336149
******************************************************************/

/*
 Description: The program is a a simple turn-based game where the player takes the role of a gladiator and challenges an opponent. Win the game by reducing the opponent's health to 0.
 Programmed by: Vince Miguel S. Jocson, S23B
 Last modified: <date when last revision was made>
 Version: 3
 [Acknowledgements: stdlib.h, time.h, https://www.codingninjas.com/studio/library/random-function-in-c, https://www.geeksforgeeks.org/time-delay-c/, https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c]
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* This function clears the output screen.
 Precondition: needs stdlib.h
 @return 
*/
void
clrscr(){
    system("@cls||clear");
}

/* Adds a time delay in between codes
 Precondition: Parameter cannot be negative. Needs time.h
 @param number_of_seconds is the duration of the delay
 @return 
*/
void
delay(int number_of_seconds){
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

/* Displays the title screen.
 Precondition: 
 @param 
 @return 
*/
void 
displayTitleScreen(){
	printf("%90s", "  ________.__              .___.__        __                \n");
	printf("%90s", " /  _____/|  | _____     __| _/|__|____ _/  |_  ___________ \n");
	printf("%90s", "/   \\  ___|  | \\__  \\   / __ | |  \\__  \\\\   __\\/  _ \\_  __ \\\n");
	printf("%90s", "\\    \\_\\  \\  |__/ __ \\_/ /_/ | |  |/ __ \\|  | (  <_> )  | \\/\n");
	printf("%90s", " \\______  /____(____  /\\____ | |__(____  /__|  \\____/|__|   \n");
	printf("%90s", "        \\/          \\/      \\/         \\/                   \n");

	printf("\n\n\n\n%62s", "1: Yes\n");
	printf("%61s", "2: No\n");
	printf("%66s", "3: How to play\n");
	printf("%71s", "4: Enter Developer Mode\n\n");
	printf("%66s", "Enter the Arena? ");
}

/* Displays a loading screen with 1 second delay
 Precondition: 
 @param 
 @return 
*/
void 
displayLoadingScreen(){
	printf("Loading...");
	delay(1);
	clrscr();
}

/* Displays a tutorial screen
 Precondition: 
 @param *response is used to store value in the response variable
 @return 
*/
void
displayTutorial(int *response){
	clrscr();
	printf("%66s", "How to play:\n");
	printf("\n");
	printf("%82s", "Defeat your opponent by reducing its HP to 0.\n");
	printf("\n");
	printf("%75s", "Select an action on each turn:\n");
	printf("\n");
	printf("%89s", "1. Attack: Deal damage to your enemy. Scales with ATK stat.\n");
	printf("\n");
	printf("%92s", "2. Block: Block damage for the current turn. Scales with DEF stat.\n");
	printf("\n");
	printf("%90s", "3. Charge: Increase your ATK and SPD for the next turn only.\n");
	printf("%83s", "Charge buff or its duration cannot be stacked.\n");
	printf("%101s", "Your charge buff will wear off after that turn regardless of what action selected.\n");
	printf("\n");
	printf("%83s", "The action of who has higher SPD will go first.\n");
	printf("%93s", "If SPD stats are equal then actions will be done at the same time.\n");
	printf("\n");
	printf("%82s", "Defeat your opponent by reducing its HP to 0.\n");
	printf("\n");
	printf("%73s", "Enter any number to continue: ");
	scanf("%d", &*response);
}

/* Displays the weapon selection screen and gets the weapon value from user. Updates player stats after.
 Precondition: user input must be a nonnegative integer
 @param 
 @return 
*/
void 
displayWeaponSelection(int *weapon, int *ATK, int *SPD){
	do{
		printf("%69s", "Choose your weapon:\n");
		printf("\n");
		printf("%75s", "1. Dagger: ATK +15, SPD +3     \n");
		printf("%75s", "2. Katana: ATK +20             \n");
		printf("%75s", "3. Broad Sword: ATK +40, SPD -5\n");
		printf("%75s", "4. Fist (No Weapon): SPD +10   \n");
		printf("\n");
		printf("%68s", "Choose between 1-4: ");
		scanf("%d", &*weapon);
		printf("\n");
		switch(*weapon){
			case 1:
				*ATK += 15;
				*SPD += 3;
				printf("%73s", "You have chosen the Dagger.\n");
				delay(1);
				break;
			case 2:	
				*ATK += 20;
				printf("%73s", "You have chosen the Katana.\n");        
				delay(1);
				break;
			case 3:
				*ATK += 40;
				*SPD -= 5;
				printf("%75s", "You have chosen the Broad Sword.\n");
				delay(1);
				break;
			case 4:
				*SPD += 10;
				printf("%73s", "You have chosen your Fists.\n");
				delay(1);
				break;
			default:
				printf("%66s", "Invalid Response!\n");
				delay(1);
				clrscr();		
		}	
	}while (*weapon > 4 || *weapon < 1);
	clrscr();
}

/* Displays the armor selection screen and gets the armor value from user. Updates player stats after.
 Precondition: user input must be a nonnegative number
 @param *armor, *response, *HP, *DEF, and *SPD are pointers used to update the player stats after selecting weapon
 @return 
*/
void
displayArmorSelection(int *armor, int *response, int *HP, int *DEF, int *SPD){
	do{
		printf("%71s", "Choose your armor set:\n");
		printf("\n");
		printf("%81s", "1. Mythril: DEF +3, SPD +3                 \n");
		printf("%81s", "2. Chain Mail: DEF +8, HP +5               \n");
		printf("%81s", "3. Adamantite Armor: DEF +18, HP +5, SPD -4\n");
		printf("%81s", "4. Bare (No Armor): SPD +10                \n");
		printf("\n");
		printf("%68s", "Choose between 1-4: ");
		scanf("%d", &*armor);
		printf("\n");
		switch(*armor){
			case 1:
				*DEF += 3;
				*SPD += 3;
				printf("%78s", "You have chosen to use the Mythril Armor.");
				delay(1);
				break;				
			case 2:
				*DEF += 8;
				*HP += 5;
				printf("%80s", "You have chosen to use the Chain Mail Armor.");
				delay(1);
				break;
			case 3:
				*DEF += 18;
				*HP += 10;
				*SPD -= 4;
				printf("%81s", "You have chosen to use the Adamantite Armor.");
				delay(1);
				break;
			case 4:
				*SPD += 10;
				printf("%72s", "You have chosen to be Bare.");
				delay(1);
				break;
			default:	
				printf("%66s", "Invalid Response!");
				delay(1);
				clrscr();
		}
	} while (*armor > 4 || *armor < 1);
	clrscr();		
}

/* Generates random number to be assigned to the enemy weapon variable. Updates enemy stats after.
 Precondition: 
 @param eweapon, eatk, espd are pointers used to update the enemy stats after selecting weapon
 @return 
*/
void 
enemyWeaponSelection(int *eweapon, int *eATK, int *eSPD){
	*eweapon = (rand() % 4) + 1;
	
	switch (*eweapon)
	{
		case 1:
			*eATK += 15;
			*eSPD += 3;
			break;
		case 2:
			*eATK += 20;
			break;
		case 3:
			*eATK += 40;
			*eSPD -= 5;
			break;
		case 4:
			*eSPD += 10;
			break;
	}
}

/* Generates random number to be assigned to the enemy armor variable. Updates enemy stats after.
 Precondition: 
 @param *earmor, *eHP, *eDEF, *eSPD are pointers used to update the enemy stats after selecting armor
 @return 
*/
void 
enemyArmorSelection(int *earmor, int *eHP, int *eDEF, int *eSPD){
	*earmor = (rand() % 4) + 1;
	
	switch (*earmor)
	{
		case 1:
			*eDEF += 3;
			*eSPD += 3;
			break;
		case 2:
			*eDEF += 8;
			*eHP += 5;
			break;
		case 3:
			*eDEF += 18;
			*eHP += 10;
			*eSPD -= 4;
			break;
		case 4:
			*eSPD += 10;
			break;
	}
}

/* Displays the screen that summarizes player stats after gear.
 Precondition: 
 @param *weapon, *armor, *HP, *ATK, *DEF, *SPD, *response are pointers used to point to the stat values and variables to be used for displaying.
 @return 
*/
void 
displayPlayerStats(int *weapon, int *armor, int *HP, int *ATK, int *DEF, int *SPD, int *response){
	do{
		printf("%72s", "Currently equipped gear:\n");
		printf("\n");
		switch (*weapon){
			case 1:
				printf("%66s", "Weapon: Dagger\n");
				break;
			case 2:
				printf("%66s", "Weapon: Katana\n");
				break;
			case 3:
				printf("%69s", "Weapon: Broad Sword\n");
				break;
			case 4:
				printf("%65s", "Weapon: Fist\n");
				break;
		}
		switch (*armor){
			case 1:
				printf("%66s", "Armor: Mythril\n");
				break;
			case 2:
				printf("%68s", "Armor: Chain Mail\n");
				break;
			case 3:
				printf("%71s", "Armor: Adamantite Armor\n");
				break;
			case 4:
				printf("%64s", "Armor: Bare\n");
				break;
		}
		printf("\n");
		printf("%74s", "Stats after equipping gear:\n\n");
		printf("					    HP  = 100    >>>    HP  = %d\n", *HP);
		printf("					    ATK = 10     >>>    ATK = %d\n", *ATK);
		printf("					    DEF = 10     >>>    DEF = %d\n", *DEF);
		printf("					    SPD = 10     >>>    SPD = %d\n", *SPD);
		printf("\n");
		printf("%77s", "1: Proceed 2: Go back to selection: ");
		scanf("%d", &*response);
		switch(*response){
			case 1:
				clrscr();
				break;
			case 2:
				clrscr();
				break;
			default:
				printf("%66s", "Invalid Response!");
				delay(1);
				clrscr();
		}	
	}while (*response != 1 && *response != 2);
}

/* Displays the gear enemy is using for the battle. Runs a countdown after.
 Precondition: 
 @param *eweapon and *earmor are pointers used to point to the variables to be used for displaying.
 @return 
*/
void 
displayEnemyGear(int *eweapon, int *earmor){
	int i;
	printf("%79s", "Your challenger has selected his arms:\n");
	switch (*eweapon){
		case 1:
			printf("%66s", "Weapon: Dagger\n");
			break;
		case 2:
			printf("%66s", "Weapon: Katana\n");
			break;
		case 3:
			printf("%69s", "Weapon: Broad Sword\n");
			break;
		case 4:
			printf("%65s", "Weapon: Fist\n");
			break;
	}
	switch (*earmor){
		case 1:
			printf("%66s", "Armor: Mythril\n");
			break;
		case 2:
			printf("%68s", "Armor: Chain Mail\n");
			break;
		case 3:
			printf("%71s", "Armor: Adamantite Armor\n");
			break;
		case 4:
			printf("%64s", "Armor: Bare\n");
			break;
	}	
	printf("\n");
	for (i = 3; i > 0; i--){
		printf("%58d\n", i);
		delay(1);
	}
	printf("\n");
	printf("%70s", "Entering the arena...");
	delay(1);
	clrscr();
}

/* Displays the a loading screen before the battle phase
 Precondition: 
 @param 
 @return 
*/
void 
displayPreGameLoading(){
	printf("Get ready for the next battle...");
	delay(1);
	clrscr();
}

/* Displays the interface during the battle phase
 Precondition: 
 @param *weapon, *armor, *HP, *ATK, *DEF, *SPD, *response, *eweapon, *earmor, *eHP, *eATK, *eDEF, *eSPD are all the pointers needed to access the values to display.
 @return 
*/
void 
displayGameUI(int *weapon, int *armor, int *HP, int *ATK, int *DEF, int *SPD, int *response, int *eweapon, int *earmor, int *eHP, int *eATK, int *eDEF, int *eSPD){
	printf("%38s%40s\n", "Player:", "Enemy:");
	switch (*weapon){
		case 1:
			printf("%42s","Dagger     ");
			break;
		case 2:
			printf("%42s","Katana     ");   
			break;
		case 3:
			printf("%42s","Broad Sword");
			break;
		case 4:
			printf("%42s","Fist       ");
			break;
	}
	switch (*eweapon){
		case 1:
			printf("				Dagger\n");
			break;
		case 2:
			printf("				Katana\n");
			break;
		case 3:
			printf("				Broad Sword\n");
			break;
		case 4:
			printf("				Fist\n");
			break;
	}
	switch (*armor){
		case 1:
			printf("%47s", "Mythril         ");
			break;
		case 2:
			printf("%47s", "Chain Mail      ");
			break;
		case 3:
			printf("%47s", "Adamantite Armor");
			break;
		case 4:
			printf("%47s", "Bare            ");
			break;
	}
	switch (*earmor){
		case 1:
			printf("				Mythril\n\n");
			break;
		case 2:
			printf("				Chain Mail\n\n");
			break;
		case 3:
			printf("				Adamantite Armor\n\n");
			break;
		case 4:
			printf("				Bare\n\n");
			break;
	}
	printf("%33s:  %d					%s:   %d\n", "HP", *HP, "HP", *eHP);
	printf("%34s: %d					%s:  %d\n", "ATK", *ATK, "ATK", *eATK);
	printf("%34s: %d					%s:  %d\n", "DEF", *DEF, "DEF", *eDEF);
	printf("%34s: %d					%s:  %d\n\n\n", "SPD", *SPD, "SPD", *eSPD);
}

/* Generates a random number between 1 to 3 to be set as the enemy's move for the turn.
 Precondition: 
 @param *emove is the pointer that updates the enemy move per turn.
 @return 
*/
void 
enemyMove(int *emove){
	*emove = (rand() % 3) + 1;
}

/* Asks user a number to be set as their move for the turn.
 Precondition: should be a nonnegative integer 
 @param *emove is the pointer that updates the enemy move per turn.
 @return 
*/
void 
getMove(int *response){
	printf("%73s\n\n", "1. Attack     2. Block     3. Charge");
	printf("%67s", "What do you want to do?: ");
	scanf("%d", &*response);
}

/* Checks the speed stat of the player and enemy to check who has move priority in the turn
 Precondition: 
 @param *SPD, *eSPD, *priority, *epriority are the pointers used to update the value assigned to priority variable
 @return 
*/
void 
getPriority(int *SPD, int *eSPD, int *priority, int *epriority){
	*priority = 0;
	*epriority = 0;
	if (*SPD > *eSPD)
		*priority = 1;
	else if (*SPD < *eSPD)
		*epriority = 1;
	else{
		*priority = 1;
		*epriority = 1;
	}
}

/* Activates the attack status of player or enemy when used
 Precondition: 
 @param *attackstatus is used to activate the player or enemy's attack status
 @return 
*/
void 
useAttack(int *attackstatus){
	*attackstatus = 1;
}

/* Activates the block status of player or enemy when used and doubles the defense of the active blocker
 Precondition: 
 @param *blockstatus is used to activate the player or enemy's block status
 @return 
*/
void 
useBlock(int *def, int *blockstatus){
	*blockstatus = 1;
	*def *= 2;
}

/* Activates the charge status of player or enemy when used and doubles the attack and speed of the active charger
 Precondition: 
 @param *chargestatus is used to activate the player or enemy's charge status
 @return 
*/
void
useCharge(int *atk, int *spd, int *chargestatus){
	if (*chargestatus == 0){
		*chargestatus = 1;
		*atk *= 2;
		*spd *= 2;
	}
}

/* Reverts the statuses to to normal at the end of the turn.
 Precondition: 
 @param *profile, *atkstatus, *blockstatus, *chargestatus, *atk, *def, *spd are the pointers used to access the stat and status values.
 @return 
*/
void 
cleanseBuff(int *profile, int *atkstatus, int *blockstatus, int *chargestatus, int *atk, int *def, int *spd){
	*atkstatus = 0; //remove attack status
	
	if (*blockstatus == 1){ //cleanse block buff
		*def /= 2;
		*blockstatus = 0;
	}

	if (*chargestatus == 1)
		*chargestatus = 2;
	else if (*chargestatus == 2){ 		// if charge is used on the previous turn, revert the buff.
		*atk /= 2;
		*spd /= 2;
		*chargestatus = 0;
		if (*profile == 1)
			printf("%68s", "Your charge wore off.\n\n");
		else if (*profile == 2)
			printf("%69s", "Enemy's charge wore off.\n\n");	
	}
}

/* Calls the move functions depending on the value assigned to the move variable by getMove or enemyMove
 Precondition: 
 @param *move, *atkstatus, *def, *blockstatus, *atk, *spd, and *chargestatus are the pointers used to access the variable values and call the move functions.
 @return 
*/
void
doTurn(int *move, int *atkstatus, int *def, int *blockstatus, int *atk, int *spd, int *chargestatus){
	
	switch (*move){
		case 1:
			useAttack(atkstatus);
			break;
		case 2:
			useBlock(def, blockstatus);
			break;
		case 3:
			useCharge(atk, spd, chargestatus);
			break;
	}
}

/* prints the text depending on the value assigned to the move variable by getMove or enemyMove
 Precondition: 
 @param  *profile is used as an identifier for the player or enemy and *response is used as the pointer for the move player or enemy chose
 @return 
*/
void 
displayMoveText(int *profile, int *response){
	switch (*response){
		case 1:
			{
			break;	
			}
			
		case 2:
			{
			if (*profile == 1)
				printf("%72s", "You raised defense by blocking.\n"); 
			else if (*profile == 2)
				printf("%73s", "Enemy raised defense by blocking.\n");
			}
			break;
		case 3:
			{
			if (*profile == 1)
				printf("%77s", "You raised attack and speed by charging.\n");
			else if (*profile == 2)
				printf("%78s", "Enemy raised attack and speed by charging.\n");
			}
			break;
		default:
			printf("%68s", "Invalid Input!");
	}
}

/* Calling this function grants a 15% chance to activate the critical hit status of the player or enemy
 Precondition: 
 @param  *critstat is replaced by the critical status variable of the player or enemy
 @return 
*/
void 
checkCritical(int *critstat, int *critchance){
	int t;
	*critstat = 0;
	t = (rand() % 100) + 1;
	if (t <= *critchance){
		*critstat = 1;		
	}
	else{
		*critstat = 0;		
	}
}

/* Calculates the amount of damage done by an attacker's atk stat minus defense. If the critical hit status is activated, defense is ignored.
 Precondition: 
 @param  *atk ,*receiverdef, and *critstat are replaced by the attacker atk stat, receiver def stat, and the attacker critical status respectively.
 @return the damage value of the attack.
*/
int 
calculateDamage(int *atk, int *receiverdef, int *critstat){
	int damage;
	if (*critstat == 1)	//determine if crit first
		damage = *atk;	// yes its a crit
	else{				//no its not a crit
		if (*atk > *receiverdef)			
			damage = *atk - *receiverdef;
		else
			damage = 0;
	}
	return damage;
}

/* Prints the attacker's attack message after attacking.
 Precondition: 
 @param  *profile is replaced by the player or enemy's profile.
 @return 
*/
void 
displayAttackMessage(int *profile){
	if (*profile == 1)
		printf("%66s", "You chose to attack!\n");
	else if (*profile == 2)
		printf("%67s", "Enemy chose to attack!\n");
	else
		printf("%76s", "You both attacked at the same time!\n\n");
}

/* Prints the attacker's damage message after attacking.
 Precondition: 
 @param  *profile is replaced by the player or enemy's profile. *atk, *def, and *critstatus are the pointers to call calculateDamage
 @return 
*/
void 
displayDamageMessage(int *profile, int *atk, int *def, int *critstatus){
	if (*profile == 1)
		printf("				     Enemy took %d damage from your attack!\n\n", calculateDamage(atk, def, critstatus));
	else if (*profile == 2)
		printf("				     You took %d damage from enemy attack!\n\n", calculateDamage(atk, def, critstatus));
}

/* Prints "Critical Hit!"
 Precondition: 
 @param  
 @return 
*/
void 
displayCriticalMessage(){
	printf("%63s", "Critical Hit!\n");
}

/* Checks if the attack move has been played. Calls calculateDamage and displays the attack related messages depending on the player or enemy's speed.
 Precondition: Will only run if at least one atkstatus is activated
 @param  *atkstatus, *eatkstatus, *SPD, *eSPD, *ATK, *eATK, *DEF, *eDEF, *HP, *eHP, *critstatus, and *ecritstatus are the pointers needed to call the functions within this function and to access the values in main.
 @return 
*/
void 
runAttackTurn(int *atkstatus, int *eatkstatus, int *SPD, int *eSPD, int *ATK, int *eATK, int *DEF, int *eDEF, int *HP, int *eHP, int *critstatus, int *ecritstatus, int *critchance){
	int player = 1;
	int enemy = 2;
	int both = 3;
	if (*atkstatus == 1 && *eatkstatus == 1){				// if both player and enemy attacks
		if (*SPD > *eSPD){									// if player is faster than enemy,
			checkCritical(critstatus, critchance);						// check for critical hit
			*eHP -= calculateDamage(ATK, eDEF, critstatus); // subtract calculated damage from receiver hp
			displayAttackMessage(&player);					// display attack message of attacker
			if (*critstatus == 1)							// if critical hit, display critical hit message after attack message
				displayCriticalMessage();					
			displayDamageMessage(&player, ATK , eDEF, critstatus);	//display the damage message of attacker
			if (*eHP < 0)						// if HP goes below zero after attack, automatically set to zero.
				*eHP = *eHP - *eHP; 			//prevents a negative number displayed on the UI
			delay(1);
			if (*eHP > 0){  								// checks if receiver is still alive after the attack. if receiver is still alive,
				checkCritical(ecritstatus, critchance);					// repeat the same code from above to start the attack for the next attacker.
			//	printf("\n%d", *ecritstatus);
				*HP -= calculateDamage(eATK, DEF, ecritstatus);
				if (*HP < 0)
					*HP = *HP - *HP;
				displayAttackMessage(&enemy);
				if (*ecritstatus == 1)
					displayCriticalMessage();
				displayDamageMessage(&enemy, eATK ,DEF, ecritstatus);
				delay(1);
			}	
		}
		else if (*SPD < *eSPD){								// same pattern above but if enemy is faster than player
			checkCritical(ecritstatus, critchance);
			*HP -= calculateDamage(eATK, DEF, ecritstatus);
			if (*HP < 0)
				*HP = *HP - *HP;
			displayAttackMessage(&enemy);
			if (*ecritstatus == 1)
				displayCriticalMessage();
			displayDamageMessage(&enemy, eATK ,DEF, ecritstatus);
			delay(1);
			if (*HP > 0){
				checkCritical(critstatus, critchance);
				*eHP -= calculateDamage(ATK, eDEF, critstatus);
				if (*eHP < 0)
					*eHP = *eHP - *eHP;
				displayAttackMessage(&player);
				if (*critstatus == 1)
				displayCriticalMessage();
				displayDamageMessage(&player, ATK , eDEF, critstatus);
				delay(1);
			}
		}
		else{															// if enemy and player have same spd stat and both attacked,
			checkCritical(critstatus, critchance);									// check critical and calculate damage for both attackers at the same time.
			*eHP -= calculateDamage(ATK, eDEF, critstatus);
			if (*eHP < 0)
				*eHP = *eHP - *eHP;
			checkCritical(ecritstatus, critchance);
			*HP -= calculateDamage(eATK, DEF, ecritstatus);
			if (*HP < 0)
				*HP = *HP - *HP;
			displayAttackMessage(&both);								// display the attack message for both
			if (*critstatus == 1)										// display critical message for whoever lands a crit
				displayCriticalMessage();
			displayDamageMessage(&player, ATK , eDEF, critstatus);		// display damage for both.
			if (*ecritstatus == 1)
				displayCriticalMessage();
			displayDamageMessage(&enemy, eATK ,DEF, ecritstatus);
		}
	}
	else if (*atkstatus == 1 && *eatkstatus == 0){						// runs attack if only player attacked.
		checkCritical(critstatus, critchance);
		*eHP -= calculateDamage(ATK, eDEF, critstatus);
		if (*eHP < 0)
			*eHP = *eHP - *eHP;
		displayAttackMessage(&player);
		if (*critstatus == 1)
			displayCriticalMessage();
		displayDamageMessage(&player, ATK , eDEF, critstatus);
		delay(1);
	}
	else if (*atkstatus == 0 && *eatkstatus == 1){						// runs attack if only enemy attacked.
		checkCritical(ecritstatus, critchance);
		*HP -= calculateDamage(eATK, DEF, ecritstatus);
		if (*HP < 0)
			*HP = *HP - *HP;
		displayAttackMessage(&enemy);
		if (*ecritstatus == 1)
			displayCriticalMessage();
		displayDamageMessage(&enemy, eATK ,DEF, ecritstatus);
		delay(1);
	}
}

/* Displays all the attack and damage messages from player and/or enemy from the attack turn to be redisplayed without delay.
 Precondition: Will only run if at least one atkstatus is activated
 @param  *atkstatus, *eatkstatus, *SPD, *eSPD, *ATK, *eATK, *DEF, *eDEF, *HP, *eHP, *critstatus, and *ecritstatus are the pointers needed to call the functions within this function and to access the values in main.
 @return 
*/
void 
displayAttackText(int *atkstatus, int *eatkstatus, int *SPD, int *eSPD, int *HP, int *eHP, int *ATK, int *eATK, int *DEF, int *eDEF, int *critstatus, int *ecritstatus){
	if (*atkstatus == 1 && *eatkstatus == 1){
		if (*SPD > *eSPD){
			printf("%66s", "You chose to attack!\n");
			if (*critstatus == 1)
				displayCriticalMessage();
			printf("				     Enemy took %d damage from your attack!\n\n", calculateDamage(ATK, eDEF, critstatus));
			//delay(1);
			if (*eHP > 0){  // checks if enemy is still alive
				printf("%67s", "Enemy chose to attack!\n");
				if (*ecritstatus == 1)
					displayCriticalMessage();
				printf("				     You took %d damage from enemy attack!\n\n", calculateDamage(eATK, DEF, ecritstatus));
				//delay(1);
			}	
		}
		else if (*SPD < *eSPD){
			printf("%67s", "Enemy chose to attack!\n");
			if (*ecritstatus == 1)
				displayCriticalMessage();
			printf("				      You took %d damage from enemy attack!\n\n", calculateDamage(eATK, DEF, ecritstatus));
			//delay(1);
			if (*HP > 0){
				printf("%66s", "You chose to attack!\n");
				if (*critstatus == 1)
					displayCriticalMessage();
				printf("				     Enemy took %d damage from your attack!\n\n", calculateDamage(ATK, eDEF, critstatus));
				//delay(1);
			}
		}
		else{
			printf("%76s", "You both attacked at the same time!\n\n");
			//delay(1);
			if (*critstatus == 1)
				displayCriticalMessage();
			printf("				     Enemy took %d damage from your attack!\n", calculateDamage(ATK, DEF, critstatus));
			if (*ecritstatus == 1)
				displayCriticalMessage();
			printf("				      You took %d damage from enemy attack!\n\n", calculateDamage(eATK, DEF, ecritstatus));
			//delay(1);
		}
	}
	else if (*atkstatus == 1 && *eatkstatus == 0){	
		printf("%66s", "You chose to attack!\n");
		if (*critstatus == 1)
			displayCriticalMessage();
		printf("				     Enemy took %d damage from your attack!\n\n", calculateDamage(ATK, eDEF, critstatus));
		//delay(1);
	}
	else if (*atkstatus == 0 && *eatkstatus == 1){
		printf("%67s", "Enemy chose to attack!\n");
		if (*ecritstatus == 1)
			displayCriticalMessage();
		printf("				     You took %d damage from enemy attack!\n\n", calculateDamage(eATK, DEF, ecritstatus));
		//delay(1);
	}
}

/* checks if player or enemy is still alive
 Precondition: 
 @param  *hp is replaced by the player or enemy hp
 @return 0 if player or enemy is dead and 1 if still alive.
*/
int 
checkHealth(int *hp){
	if (*hp <= 0)
		return 0;
	else
		return 1;
}

/* displays the developer menu where user can freely change player and enemy stats
 Precondition: 
 @param  *HP, *ATK, *DEF, *SPD, *response, *eHP, *eATK, *eDEF, *eSPD, and *critchance are the pointers used to modify the stats
 @return 0 
*/
void
displayDeveloperMenu(int *HP, int *ATK, int *DEF, int *SPD, int *response, int *eHP, int *eATK, int *eDEF, int *eSPD, int *critchance){
	printf("%s\n\n", "Enter Player Stats:");
	
	printf("%s: ", "HP");
	scanf("%d", &*HP);
	printf("%s: ", "ATK");
	scanf("%d", &*ATK);
	printf("%s: ", "DEF");
	scanf("%d", &*DEF);
	printf("%s: ", "SPD");
	scanf("%d", &*SPD);
	printf("\n");
	
	printf("%s\n\n", "Enter Enemy Stats:");
	printf("%s: ", "HP");
	scanf("%d", &*eHP);
	printf("%s: ", "ATK");
	scanf("%d", &*eATK);
	printf("%s: ", "DEF");
	scanf("%d", &*eDEF);
	printf("%s: ", "SPD");
	scanf("%d", &*eSPD);
	printf("\n");
	
	printf("Critical Hit Chance %%: ");
	scanf("%d", &*critchance);
}

int main()
{ 	
	// ints
	int response;
	int weapon;
	int armor;
	int eweapon;
	int earmor;
	
	
	int player = 1;
	int enemy = 2;
	
	int emove;
	int priority;
	int epriority;
	int atkstatus;
	int eatkstatus;
	int chargestatus;
	int echargestatus;
	int blockstatus;
	int eblockstatus;
	int critstatus;
	int ecritstatus;
	
	int critchance;
	int HP;
	int ATK;
	int DEF;
	int SPD;
	
	//enemy stats
	int eHP;
	int eATK;
	int eDEF;
	int eSPD;
	
	do{
		displayTitleScreen();
		scanf("%d", &response);
			
		switch(response){
		case 1:
			{
				printf("\n\n\n%76s", "Welcome to the Arena, Challenger.\n");
				delay(1);
				clrscr();
				displayLoadingScreen();
				do{		//player gear selection
					HP = 100;
					ATK = 10;
					DEF = 10;
					SPD = 10;
					eHP = 100;
					eATK = 10;
					eDEF = 10;
					eSPD = 10;
					critchance = 15;
					displayWeaponSelection(&weapon, &ATK, &SPD);
					displayArmorSelection(&armor, &response, &HP, &DEF, &SPD);
					displayPlayerStats(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response);
				} while (response == 2);
				srand(time(0));
				enemyWeaponSelection(&eweapon, &eATK, &eSPD);
				enemyArmorSelection(&earmor, &eHP, &eDEF, &eSPD);
				displayPreGameLoading();
				displayEnemyGear(&eweapon, &earmor);
				
				//begin battle phase
				// set move statuses back to 0 when it loops back here. 
				atkstatus = 0;
				eatkstatus = 0;
				blockstatus = 0;
				eblockstatus = 0;
				chargestatus = 0;
				echargestatus = 0;
				// start the battle with UI
				do{
					do{
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD); // display UI
						getMove(&response);	
						if (response > 3 || response < 1){
							printf("\n%68s", "Invalid Input!");
							delay(1);
							clrscr();
						}
					} while(response > 3 || response < 1);
					enemyMove(&emove); //get enemy move
					printf("\n\n");		
					getPriority(&SPD, &eSPD, &priority, &epriority);
					if (priority > epriority){	//run the turn
						clrscr();
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD); //redisplay UI without the move options
						doTurn(&response, &atkstatus, &DEF, &blockstatus, &ATK, &SPD, &chargestatus); // player move
						displayMoveText(&player, &response);	// display player/enemy move message
						delay(1);								// short delay
						clrscr();								// clear screen and update ui
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);// redisplay the updated UI
						displayMoveText(&player, &response);			// redisplay the move message without delay to appear after UI 
						delay(1);										// short delay before next move
						
						doTurn(&emove, &eatkstatus, &eDEF, &eblockstatus, &eATK, &eSPD, &echargestatus); // enemy move
						printf("\n");						// add a space before the next move message
						displayMoveText(&enemy, &emove);	// display enemy move message, should have 2 messages by now
						delay(1);							// short delay
						clrscr();							// clear screen and update UI again
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD); // redisplay the updated the UI
						displayMoveText(&player, &response);
						displayMoveText(&enemy, &emove);	//redisplay both player and enemy move message without delay
						printf("\n");						// add space in case there is another message to appear later on
					}
					else if (priority < epriority){ // same thing but if enemy is faster
						clrscr();
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);
						doTurn(&emove, &eatkstatus, &eDEF, &eblockstatus, &eATK, &eSPD, &echargestatus);
						displayMoveText(&enemy, &emove);
						delay(1);
						clrscr();
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);
						displayMoveText(&enemy, &emove);
						delay(1);
						
						doTurn(&response, &atkstatus, &DEF, &blockstatus, &ATK, &SPD, &chargestatus);
						printf("\n");
						displayMoveText(&player, &response);
						delay(1);
						clrscr();
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);
						displayMoveText(&enemy, &emove);
						displayMoveText(&player, &response);
						printf("\n");
					
					}
					else{
						clrscr();
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);
						doTurn(&response, &atkstatus, &DEF, &blockstatus, &ATK, &SPD, &chargestatus);
						doTurn(&emove, &eatkstatus, &eDEF, &eblockstatus, &eATK, &eSPD, &echargestatus);
						displayMoveText(&player, &response);
						displayMoveText(&enemy, &emove);
						delay(1);
						clrscr();
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);
						displayMoveText(&player, &response);
						displayMoveText(&enemy, &emove);
						printf("\n");		
					}
					if (atkstatus == 1 || eatkstatus == 1){
						runAttackTurn(&atkstatus, &eatkstatus, &SPD, &eSPD, &ATK, &eATK, &DEF, &eDEF, &HP, &eHP, &critstatus, &ecritstatus, &critchance);
					}
					clrscr();
					
					//////////////////////////////////////////////////////// REDISPLAY SCREEN
					
					displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);
					
					if (priority > epriority){
						displayMoveText(&player, &response);		
						printf("\n");									
						displayMoveText(&enemy, &emove);
						printf("\n");	
					}
					else if (priority < epriority){
						displayMoveText(&enemy, &emove);
						printf("\n");
						displayMoveText(&player, &response);
						printf("\n");
					}
					else{
						displayMoveText(&player, &response);
						displayMoveText(&enemy, &emove);
						printf("\n");			
					}
	
					if (atkstatus == 1 || eatkstatus == 1){
						displayAttackText(&atkstatus, &eatkstatus, &SPD, &eSPD, &HP, &eHP, &ATK, &eATK, &DEF, &eDEF, &critstatus, &ecritstatus);
					}
					
					
					cleanseBuff(&player, &atkstatus, &blockstatus, &chargestatus, &ATK, &DEF, &SPD);
					cleanseBuff(&enemy, &eatkstatus, &eblockstatus, &echargestatus, &eATK, &eDEF, &eSPD);
					
					if (checkHealth(&HP) == 1 && checkHealth(&eHP) == 1){
						printf("%70s", "Enter 1 to continue: ");
						scanf("%d", &response);
						if (response == 1)
							clrscr();
						else printf ("\n\n%68s", "\nInvalid Response!");	
					}
					else if (checkHealth(&HP) == 1 && checkHealth(&eHP) == 0){
						printf("%77s", "Enemy health has been reduced to zero!\n\n");
						delay(1);
						printf("%84s", "You have won the battle and claimed blood and glory.\n\n");
						printf("%79s", "Enter 1 to go back to title screen: ");
						scanf("%d", &response);
					}
					else if (checkHealth(&HP) == 0 && checkHealth(&eHP) == 1){
						printf("%77s", "Your health has been reduced to zero...\n\n");
						delay(1);
						printf("%83s", "You have spilled your blood and lost this battle.\n\n");
						printf("%79s", "Enter 1 to go back to title screen: ");
						scanf("%d", &response);
					}
					else if (checkHealth(&HP) == 0 && checkHealth(&eHP) == 0){
						printf("%85s", "Both you and your enemy's health were reduced to zero!\n\n");
						delay(1);
						printf("%71s", "The battle ends in a draw!\n\n");
						printf("%79s", "Enter 1 to go back to title screen: ");
						scanf("%d", &response);
					}
					
				}while (checkHealth(&HP) == 1 && checkHealth(&eHP) == 1); 	
				clrscr();
				displayLoadingScreen();		
			}
			break;
		case 2:
			printf("\n\n\n%62s", "Coward!\n");
			break;
		case 3:
			{
				displayTutorial(&response);
				if (response == 1)
					clrscr();
			}
			break;
		case 4:
			{
				do{
					clrscr();
					HP = 100;
					ATK = 10;
					DEF = 10;
					SPD = 10;
					eHP = 100;
					eATK = 10;
					eDEF = 10;
					eSPD = 10;
					displayDeveloperMenu(&HP, &ATK, &DEF, &SPD, &response, &eHP, &eATK, &eDEF, &eSPD, &critchance);
					do{
						printf("\n\nPress 1 to confirm stats, press 2 to set again: ");
						scanf("%d", &response);
						if (response != 1 && response != 2){
							printf("Invalid Input!");
							delay(1);
						} 
					} while (response != 1 && response != 2);
					
				} while (response != 1);
				srand(time(0));
				//displayPreGameLoading();
				//begin battle phase
				// set move statuses back to 0 when it loops back here. 
				atkstatus = 0;
				eatkstatus = 0;
				blockstatus = 0;
				eblockstatus = 0;
				chargestatus = 0;
				echargestatus = 0;
				clrscr();
				// start the battle with UI
				do{
					do{
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD); // display UI
						getMove(&response);	
						if (response > 3 || response < 1){
							printf("\n%68s", "Invalid Input!");
							delay(1);
							clrscr();
						}
					} while(response > 3 || response < 1);
					enemyMove(&emove); //get enemy move
					printf("\n\n");		
					getPriority(&SPD, &eSPD, &priority, &epriority);
					if (priority > epriority){	//run the turn
						clrscr();
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD); //redisplay UI without the move options
						doTurn(&response, &atkstatus, &DEF, &blockstatus, &ATK, &SPD, &chargestatus); // player move
						displayMoveText(&player, &response);	// display player/enemy move message
						delay(1);								// short delay
						clrscr();								// clear screen and update ui
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);// redisplay the updated UI
						displayMoveText(&player, &response);			// redisplay the move message without delay to appear after UI 
						delay(1);										// short delay before next move
						
						doTurn(&emove, &eatkstatus, &eDEF, &eblockstatus, &eATK, &eSPD, &echargestatus); // enemy move
						printf("\n");						// add a space before the next move message
						displayMoveText(&enemy, &emove);	// display enemy move message, should have 2 messages by now
						delay(1);							// short delay
						clrscr();							// clear screen and update UI again
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD); // redisplay the updated the UI
						displayMoveText(&player, &response);
						displayMoveText(&enemy, &emove);	//redisplay both player and enemy move message without delay
						printf("\n");						// add space in case there is another message to appear later on
					}
					else if (priority < epriority){ // same thing but if enemy is faster
						clrscr();
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);
						doTurn(&emove, &eatkstatus, &eDEF, &eblockstatus, &eATK, &eSPD, &echargestatus);
						displayMoveText(&enemy, &emove);
						delay(1);
						clrscr();
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);
						displayMoveText(&enemy, &emove);
						delay(1);
						
						doTurn(&response, &atkstatus, &DEF, &blockstatus, &ATK, &SPD, &chargestatus);
						printf("\n");
						displayMoveText(&player, &response);
						delay(1);
						clrscr();
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);
						displayMoveText(&enemy, &emove);
						displayMoveText(&player, &response);
						printf("\n");
					
					}
					else{
						clrscr();
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);
						doTurn(&response, &atkstatus, &DEF, &blockstatus, &ATK, &SPD, &chargestatus);
						doTurn(&emove, &eatkstatus, &eDEF, &eblockstatus, &eATK, &eSPD, &echargestatus);
						displayMoveText(&player, &response);
						displayMoveText(&enemy, &emove);
						delay(1);
						clrscr();
						displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);
						displayMoveText(&player, &response);
						displayMoveText(&enemy, &emove);
						printf("\n");		
					}
					if (atkstatus == 1 || eatkstatus == 1){
						runAttackTurn(&atkstatus, &eatkstatus, &SPD, &eSPD, &ATK, &eATK, &DEF, &eDEF, &HP, &eHP, &critstatus, &ecritstatus, &critchance);
					}
					clrscr();
					
					//////////////////////////////////////////////////////// REDISPLAY SCREEN
					
					displayGameUI(&weapon, &armor, &HP, &ATK, &DEF, &SPD, &response, &eweapon, &earmor, &eHP, &eATK, &eDEF, &eSPD);
					
					if (priority > epriority){
						displayMoveText(&player, &response);		
						printf("\n");									
						displayMoveText(&enemy, &emove);
						printf("\n");	
					}
					else if (priority < epriority){
						displayMoveText(&enemy, &emove);
						printf("\n");
						displayMoveText(&player, &response);
						printf("\n");
					}
					else{
						displayMoveText(&player, &response);
						displayMoveText(&enemy, &emove);
						printf("\n");		
					}
	
					if (atkstatus == 1 || eatkstatus == 1){
						displayAttackText(&atkstatus, &eatkstatus, &SPD, &eSPD, &HP, &eHP, &ATK, &eATK, &DEF, &eDEF, &critstatus, &ecritstatus);
					}
					
					
					cleanseBuff(&player, &atkstatus, &blockstatus, &chargestatus, &ATK, &DEF, &SPD);
					cleanseBuff(&enemy, &eatkstatus, &eblockstatus, &echargestatus, &eATK, &eDEF, &eSPD);
					
					if (checkHealth(&HP) == 1 && checkHealth(&eHP) == 1){
						printf("%70s", "Enter 1 to continue: ");
						scanf("%d", &response);
						if (response == 1)
							clrscr();
						else printf ("\n\n%68s", "\nInvalid Response!\n");	
					}
					else if (checkHealth(&HP) == 1 && checkHealth(&eHP) == 0){
						printf("%77s", "Enemy health has been reduced to zero!\n\n");
						delay(1);
						printf("%84s", "You have won the battle and claimed blood and glory.\n\n");
						printf("%79s", "Enter 1 to go back to title screen: ");
						scanf("%d", &response);
					}
					else if (checkHealth(&HP) == 0 && checkHealth(&eHP) == 1){
						printf("%77s", "Your health has been reduced to zero...\n\n");
						delay(1);
						printf("%83s", "You have spilled your blood and lost this battle.\n\n");
						printf("%79s", "Enter 1 to go back to title screen: ");
						scanf("%d", &response);
					}
					else if (checkHealth(&HP) == 0 && checkHealth(&eHP) == 0){
						printf("%85s", "Both you and your enemy's health were reduced to zero!\n\n");
						delay(1);
						printf("%71s", "The battle ends in a draw!\n\n");
						printf("%79s", "Enter 1 to go back to title screen: ");
						scanf("%d", &response);
					}
					
				}while (checkHealth(&HP) == 1 && checkHealth(&eHP) == 1); 	
				clrscr();
				displayLoadingScreen();		
			}
			break;
		default:
			printf("\n\n\n%68s","Invalid Response!\n");
			delay(1);
			clrscr();
		}		
	} while (response != 2);
	
	return 0;
}

