#include <stdio.h>

// actions taken during the game change these stats, making some actions unavoidable based off of decisions
int curiosity = 0; // actions that encourage exploration increase. actions that show disregardance decrease
int intelligence = 0; // actions that show smarts increase. actions that aren't decrease.
int brave = 0; // Actions that show headstrong capabilities. Actions that show cowardice decrease
int honest = 0; // actions that are truthful increase. Actions that are decietful decrease.
int charisma = 0; //actions that are charming increase. Actions that are blunt decrease.
int actionMeter = 50;


// flags that trigger certain events (butterfly effect)  
int introFlag = 0; // Flag to set off Action Meter functionality once it is equal to 1.
int flag1 = 0; // Henry told player of his missing wristwatch
int flag1_5 = 0; // Found wristwatch in the ballroom
int flag2 = 0; // Henry told player about the porcelein dish shards.
int flag2_5 = 0; // Found porcelein shards in the trash can
int flag3 = 0; // Deborah tells player her alibi.
int flag3_5 = 0; // Evelyn tells the player about Deborah's wearabouts.
int flag4 = 0; // Evelyn tells the player about Deborah's wearabouts again.
int flag4_5 = 0; // Deborah explains her alibi again
int flag5 = 0; // Loretta tells the player about Jacob and Edward's departure from the manor.
int flag5_5 = 0; // Jacob tells the player his alibi
int flag5_75= 0; // Edwards tells player his alibi
int flag6 = 0; // Loretta tells player to talk over Jacob's demeanor with Edward.



enum Room {  // Defines the rooms in the manor as enumeration variables
    ENTRANCE_HALL,
    BALLROOM,
    DINING_ROOM, 
    LIBRARY,
    KITCHEN,
    GUEST_ROOM,
    STUDY,
    CONSERVATORY,
    HALLWAY,
    GARDENS,
    LAKE
};

enum Room currentRoom = ENTRANCE_HALL; // Starting room is the Entrance Room

// function prototypes. Implemented these as functions go in circles, and can't declare them before calling them
void writeFile();
void readFile();
void welcome();
void enter();
void familyDialogue();
void entranceHall();
void ballroom();
void diningRoom();
void library();
void kitchen();
void guestRoom();
void study();
void conservatory();
void hallway();
void gardens();
void lake();
void henryInterrogation();
void deborahInterrogation();
void lorettaInterrogation();
void jacobInterrogation();
void investigateOrLeave();
void roomChangeSelection();
void roomChangeLibrary(enum Room room);
int main();

// User Inputs throughout the game

char UserInput1; // Open Case File? (Y/N)
char UserInput2; // Who to approach at the Entrance Hall? (1,2,3,4,5). They are chars to account for invalid inputs.
char UserInput3; // What would you like to ask the Entrance Hall family members? (1,2,3,4,0). They are chars to account for invalid inputs
int UserInput4; // Where would you like to go? (1, 2, 3, 4, 5)
char UserInput5; // Investigate or Leave? (1, 2)
char UserInput6; // Investigate Ballroom
char UserInput7; // Investigate Dining Room
char UserInput8; // Investigate Library
char UserInput9; // Investigate Kitchen
char UserInput10; // Investigate Guest Room
char UserInput11; // Investigate Study Room
char UserInput12; // Investigate Conservatory
char UserInput13; // Investigate Hallway
char UserInput14; // Investigate Gardens
char UserInput15; // Investigate Lake
char UserInput16; // Henry Interrogation
char UserInput17; // Deborah Interrogation
char UserInput18; // Loretta Interrogation
char UserInput19; // Jacob Interrogation


void decreaseActionMeter(){
    if(introFlag){
        actionMeter--;
    }
}

void printActionMeter() {  // Prints the action meter as a bar with every "=" being an interatction. After every interaction a "=" dissapears.
    if(introFlag){
        int remaining = actionMeter;
        printf("\033[s\033[100;%dHAction Meter: [", 75);
        for (int i = 0; i < 50; i++) {
            if (i < remaining) {
              printf("=");
            } else {
            printf(" ");
            }
        }
        printf("] %d\033[u", actionMeter);
    }
}

void writeFile(){
    FILE *caseFile = fopen("CaseFile.txt", "w");  // Creates a Case File for the game that can be accessed by players
    if(caseFile == NULL){ // Checks to make sure the file was created successfully
        printf("Sorry! There was an error creating the case file!");
    }
    fprintf(caseFile, "\n\n*Case File: Ravenwood Ruby*\n\n");
    fprintf(caseFile, "_Pembroke Manor Map_:\n\n");
    fprintf(caseFile, "          ________________________________________________________________\n");
    fprintf(caseFile, "         |                             |                      |           |\n");
    fprintf(caseFile, "         |          *Ballroom*         |       *Kitchen*      |   *Guest  |\n");
    fprintf(caseFile, "         |_____________________________|                      |   Room*   |\n");
    fprintf(caseFile, "         |                             |        *Dining       |           |\n");
    fprintf(caseFile, "         |          *Library*          |         Room*        |           |\n");
    fprintf(caseFile, "         |_____________________________|______________________|           |\n");
    fprintf(caseFile, "         |                             |                      |           |\n");
    fprintf(caseFile, "         |          *Entrance*         |       *Study*        |           |\n");
    fprintf(caseFile, "         |_____________________________|______________________|           |\n");
    fprintf(caseFile, "         |                             |                      |           |\n");
    fprintf(caseFile, "         |          *Hallway*          |      *Conservatory*  |           |\n");
    fprintf(caseFile, "         |_____________________________|______________________|___________|\n");
    fprintf(caseFile, "\n");
    fprintf(caseFile, "_Outside Areas_:\n\n");
    fprintf(caseFile, "      ________________\n");
    fprintf(caseFile, "     |                |\n");
    fprintf(caseFile, "     |   *Gardens*    |\n");
    fprintf(caseFile, "     |________________|\n");
    fprintf(caseFile, "          |    |\n");
    fprintf(caseFile, "          |    |\n");
    fprintf(caseFile, "          |    |\n");
    fprintf(caseFile, "  ___________________\n");
    fprintf(caseFile, " |                   |\n");
    fprintf(caseFile, " |      *Lake*       |\n");
    fprintf(caseFile, " |___________________|\n");
    fprintf(caseFile, "*Pembroke Manor Description*:\n\n");
    fprintf(caseFile, " - _Location_: Ravenwood, England\n");
    fprintf(caseFile, " - _Architecture_: Gothic-style mansion\n");
    fprintf(caseFile, " - _Size_: Spacious, with multiple wings and levels\n");
    fprintf(caseFile, " - _Features_: Grand entrance hall, library, ballroom, conservatory\n");
    fprintf(caseFile, " - _Surroundings_: Extensive gardens, wooded areas, and a nearby lake\n");
    fprintf(caseFile, " - _Rumors_: Said to be haunted by the ghost of a former occupant, with hidden passages and secret rooms\n\n");
    fprintf(caseFile, "*Pembroke Manor History*:\n\n");
    fprintf(caseFile, "   Pembroke Manor has a rich and storied past, dating back to the 19th century when it was built by the Pembroke family.\n");
    fprintf(caseFile, "   Over the years, it has served as a symbol of wealth, prestige, and power, witnessing numerous events and gatherings of the aristocracy.\n");
    fprintf(caseFile, "   The manor has weathered wars, economic downturns, and societal changes, yet it remains standing as a testament to the legacy of its builders.");
    fprintf(caseFile, "   Many tales and legends surround the manor, adding to its mystique and allure.\n\n");
    fprintf(caseFile, "*Description of the Ravenwood Ruby*:\n\n");
    fprintf(caseFile, " - _Name_: Ravenwood Ruby\n");
    fprintf(caseFile, " - _Description_: A rare and exquisite gemstone, known for its deep red color and flawless clarity. The Ravenwood Ruby is said to be as valuable as it is mysterious, with a history shrouded in myth and legend. According to Pembroke family lore, the ruby was acquired by an ancestor on a journey to distant lands, where it was rumored to possess magical properties. Over the years, the ruby has been passed down through generations, serving as a symbol of power and prosperity for the Pembroke family.\n");
    fprintf(caseFile, " - _Current Status_: Missing, believed to have been stolen from Pembroke Manor's Study Room under mysterious circumstances. Its disappearance has cast a shadow over the manor and sparked a desperate search for its whereabouts.\n\n");
    fprintf(caseFile, "*Guest Profiles*:\n\n");
    fprintf(caseFile, "1. _Sir Reginald Pembroke_:\n");
    fprintf(caseFile, "   - *Relationship*: Patriarch of the Pembroke family\n");
    fprintf(caseFile, "   - *Personality*: Authoritative, traditional, protective of his family\n");
    fprintf(caseFile, "   - *Background*: Inherited Pembroke Manor from his ancestors, known for his philanthropy\n\n");
    fprintf(caseFile, "2. _Lady Evelyn Pembroke_:\n");
    fprintf(caseFile, "   - *Relationship*: Wife of Sir Reginald Pembroke\n");
    fprintf(caseFile, "   - *Personality*: Charismatic, sociable, with a hint of mystery\n");
    fprintf(caseFile, "   - *Background*: Married Sir Reginald Pembroke for his wealth, rumored to have a colorful past\n\n");
    fprintf(caseFile, "3. _Lord Edward Pembroke_:\n");
    fprintf(caseFile, "   - *Relationship*: Son of Sir Reginald and Lady Evelyn Pembroke\n");
    fprintf(caseFile, "   - *Personality*: Charming, charismatic, but reckless and impulsive\n");
    fprintf(caseFile, "   - *Background*: Known for his extravagant lifestyle and gambling habits, often at odds with his father's expectations\n\n");
    fprintf(caseFile, "4. _Miss Victoria Pembroke_:\n");
    fprintf(caseFile, "   - *Relationship*: Daughter of Sir Reginald and Lady Evelyn Pembroke\n");
    fprintf(caseFile, "   - *Personality*: Independent, passionate, with a strong sense of justice\n");
    fprintf(caseFile, "   - *Background*: Estranged from her family due to her non-conformist beliefs, returned to Pembroke Manor for the first time in years\n\n");
    fprintf(caseFile, "*Staff Member Profiles*:\n\n");
    fprintf(caseFile, "1. _Butler_:\n");
    fprintf(caseFile, "   - *Role*: Manor's head butler\n");
    fprintf(caseFile, "   - *Appearance*: Impeccably dressed in a traditional butler uniform\n");
    fprintf(caseFile, "   - *Background*: Loyal servant of the Pembroke family for decades, known for his discretion and efficiency\n\n");
    fprintf(caseFile, "2. _Housekeeper_:\n");
    fprintf(caseFile, "   - *Role*: Head housekeeper\n");
    fprintf(caseFile, "   - *Appearance*: Neat and tidy, with a no-nonsense demeanor\n");
    fprintf(caseFile, "   - *Background*: Overseeing the cleanliness and organization of Pembroke Manor for years, respected by the staff\n\n");
    fprintf(caseFile, "3. _Gardener_:\n");
    fprintf(caseFile, "   - *Role*: Manor's gardener\n");
    fprintf(caseFile, "   - *Appearance*: Wearing gardening attire, with dirt-stained hands and a friendly smile\n");
    fprintf(caseFile, "   - *Background*: Tending to the extensive gardens of Pembroke Manor with dedication and care, knowledgeable about plants and landscaping\n\n");
    fprintf(caseFile, "4. _Cook_:\n");
    fprintf(caseFile, "   - *Role*: Manor's chef\n");
    fprintf(caseFile, "   - *Appearance*: Wearing a chef's hat and apron, with a bustling demeanor in the kitchen\n");
    fprintf(caseFile, "   - *Background*: Master of culinary arts, responsible for preparing exquisite meals for the Pembroke family and their guests\n\n\n");
    fprintf(caseFile, "Make sure to scroll all the way to the top of the case file! You might not be seeing the whole thing!");
    fclose(caseFile);
}

void readFile(){ // Whenever this function is called, it reads the Case File in the terminal to the user. 
    FILE *caseFile = fopen("CaseFile.txt", "r");
        if(caseFile == NULL){ // Checks to see if file can be opened.
            printf("There was a problem opening the case file!");
        }
        char buffer[1000];
        while(fgets(buffer, 1000, caseFile) != NULL){
            printf("%s", buffer);
        }
        fclose(caseFile);
}

void welcome() { // Welcome screen for the game
    printf("\033[1mWelcome to the Pembroke Family Mystery!\n\n\033[0m"
           "You are private detective Benjamin White of Ravenwood. Late last night, you were given a call from the Pembroke family about a missing heirloom, the Ravenwood Ruby.\n"
           "It is your job to investigate the Pembroke family manor, uncover its secrets, and determine what happened to the Ruby!\n"
           "Be mindful! There is more than what meets the eye in the manor, and someone is bound to try to stop your efforts of uncovering the truth!\n"
           "Your choices determine if you uncover the truth behind the Ruby, fail in your task, or find a deeper mystery within the manor. Good luck!\n");
}

void enter() { // Used to continue the story by pressing Enter
    printf("\n\e[3mPress enter to continue\e[0m\n\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void familyDialogue() {  // Dialogue options between every member of the family when in the Entrance Hall. Extensive part of the game.
    do {
        printf("\n1. Where were you last night?\n2. Do you have any suspicions?\n3. What's your relationship to everyone?\n4. Did you notice anything different?\n5. Goodbye\n");
        printf("Enter your choice (1-5): ");
        scanf(" %c", &UserInput3);
        while (getchar() != '\n');

        switch(UserInput3) {
            case '1': 
                if(UserInput2 == '1'){
                    printf("\n\033[0;33m'I was in the library archive reading. That should have been around 9:00pm.\nI didn't leave the library until Loretta, our housekeeper, stopped by to clean up the room. That should have been about 2 hours later, around 11pm.\nAfter that I went to my quarters.'\033[0m\n\n");
                    printf("\033[94m\nIntelligence +5\n\n\033[0m");
                    intelligence = intelligence + 5;
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                } else if (UserInput2 == '2'){
                    printf("\n\033[0;91;95m'Well, since you asked so nicely, I'll tell yah. I was in the guest room catching up with Victoria!\nIt's been years, and while we have our differences, it's nice catching up.\nWe were chatting from around 10pm to 12am.\nI then went to bed, as my husband fell asleep before me.'\033[0m\n\n");
                    printf("\033[94m\nCharisma +5\n\033[0m");
                    charisma = charisma + 5;
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                } else if (UserInput2 == '3'){
                    printf("\n\033[32m'I was at the Ravenwood Casino last night. I didn't get home until morning, when everyone was talking about the stolen Ruby.\nI left for the casino at around 6:30pm last night.'\033[0m\n\n");
                    flag5_75 = 1;
                    if (flag5 && flag5_5){
                    enter();
                    printf("\033[94m]This corroberates Loretta's claim about where Edward went last night.\033[0m");
                    enter();
                }
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                } else {
                    printf("\n\033[0;34m'I was in the conservatory from 9pm to 10pm. Then I went to the guest room to talk with my mother for two hours about my time in Bellow's Creek.\nNothing too interesting, honestly.'\033[0m\n\n");
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                }
            case '2':
                if(UserInput2 == '1'){
                    printf("\n\033[0;33m'I don't doubt my family in the slightest. If it was anyone here, I would have to say one of the staff members.\nThat or the occult. Y'know there are rumors of ghosts here. The gardens and the lake are the most eerie. Give me the creeps.'\033[0m\n\n");
                    printf("\033[94m\nCuriosity +5\n\033[0m");                
                    curiosity = curiosity + 5;
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                } else if (UserInput2 == '2'){
                    printf("\n\033[0;91;95m'Deborah, our gardener. She was out in the gardens late last night, as I saw her through the window. That was around 11pm.\nWhy would anyone be gardening that late?'\033[0m\n\n");
                    flag3_5 = 1;
                    printf("\033[94m\nCuriosity +5\n\033[0m");                
                    curiosity = curiosity + 5;
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                } else if (UserInput2 == '3'){
                    printf("\n\033[32m'I have two suspects in mind. First is Victoria. She comes back after years because of the missing Ruby? Why now? It's odd.\nSecond is Jacob, the cook. He's always complained about the pay he recieves not being enough for him. He might have snapped.'\033[0m\n\n");
                    printf("\033[94m\nHonest +5\n\033[0m"); 
                    honest = honest + 5;
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                } else {
                    printf("\n\033[0;34m'One of my family members no doubt. My mom is insane when it comes to jewels and my brother would more than likely gamble it away.\nNot to mention my father has a knack for pulling stunts to get the staff he doesn't like framed and fired. All psycopaths.'\033[0m\n\n");
                    printf("\033[94m\nHonest +5\n\033[0m");
                    honest = honest + 5;
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                }
            case '3':
                if(UserInput2 == '1'){
                    printf("\n\033[0;33m'I trust my family didn't have involvement in the Ruby's disappearance.\nHowever, Victoria and the family haven't been on the best terms these last few years.\nAs for the staff, I can't say anyone has been outwardly suspicious.'\033[0m\n\n");
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                } else if (UserInput2 == '2'){
                    printf("\n\033[0;91;95m'Honestly, Reginald and I don't get along too well. Though he does know how to treat a lady.\nEdward and I on the other hand are very close. We talk everyday.\nFinally, I couldn't really care about the staff. I don't notice them.'\033[0m\n\n");
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                } else if (UserInput2 == '3'){
                    printf("\n\033[32m'Oh, boy where to start?\nMy father wants me to be like him, but I'm nothing like him. My mother understands me better than he ever could.\nVictoria betrayed the family by leaving us behind and moving to Bellow's Creek. She's not a real Pembroke.\nAs for the staff, I like them for the most part. Deborah is extrememly kind, Loretta understands me better than everyone, even my mother, and Henry, the butler, caters to all of us.\nThe only one I don't like is Jacob, the cook.'\033[0m\n\n");
                    printf("\033[94m\nHonest +5\n\033[0m");
                    curiosity = curiosity + 5;
                    honest = honest + 5;
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                } else {
                    printf("\n\033[0;34m'I was always closer to the staff. They are the sanest people I've met; although I haven't seen them in years.\nI'm closest to Henry, the butler. He's always been kind and honest to me.'\033[0m\n\n");
                    printf("\033[94m\nHonest +5\n\033[0m");
                    honest = honest + 5;
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                }
            case '4':
                if(UserInput2 == '1'){
                    printf("\n\033[0;33m'Actually, yes! As I was reading in the library, there was music in the ballroom playing more loudly than usual.\nI went to turn it down to continue reading, but no one was in the ballroom. That was around 10:30pm.\nAfter turning the music down, I went back to my reading. That should have been around 10:45pm.\nI must say, music turning on by itself sounds like the occult, doesn't it?'\033[0m\n\n");
                    printf("\033[94m\nIntelligence +5, Curiousity +5\n\033[0m");
                    intelligence = intelligence + 5;
                    curiosity = curiosity + 5;
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                } else if (UserInput2 == '2'){
                    printf("\n\033[0;91;95m'I recall seeing Deborah in the garden around 11pm through the guest room window.\nI also wouldn't say it's suspicious, but I thought I heard glass shattering at around 20 minutes before I saw Deborah.\nI looked around but couldn't find anything, so I must have been hearing things.'\033[0m\n\n");
                    flag4 = 1;
                    printf("\033[94m\nIntelligence +5, Curiousity +5\n\033[0m");
                    intelligence = intelligence + 5;
                    curiosity = curiosity + 5;
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                } else if (UserInput2 == '3'){
                    printf("\n\033[32m'Not a clue. I wasn't here when the Ruby was stolen. I left at around 8:30pm and nothing seemed off or out of place when I left.'\033[0m\n\n");
                    decreaseActionMeter();
                    printActionMeter();
                    break;                                        
                } else {
                    printf("\n\033[0;34m'I heard a bit of glass shattering yesterday when I was in the guest room with my mother. It was very faint, but I heard it.\nI asked the staff about it, and Henry, the butler, broke a few dishes.'\033[0m\n\n");
                    printf("\033[94m\nIntelligence +5\033[0m");
                    intelligence = intelligence + 5;
                    decreaseActionMeter();
                    printActionMeter();
                    break;
                }
            case '5':
                if(UserInput2 == '1'){
                    printf("\n\033[0;33m\nI'm wishing you success, Detective White.\n\n\033[0m");
                    break;
                } else if (UserInput2 == '2'){
                    printf("\n\033[0;91;95m'Come back anytime you'd like, Mister White.'\033[0m\n\n");
                    break;
                } else if (UserInput2 == '3'){
                printf("\n\033[32m'Let me know if you need anything else! I'd be happy to help!'\033[0m\n\n");
                    break;                      
                } else {
                    printf("\n\033[0;34m'Find the theif in the family and make them pay.'\033[0m\n\n");
                    break;
                }
            default: 
                printf("\n\nInvalid option! Please enter a number from 1 to 5.\n");
        }
    } while (UserInput3 != '5' && actionMeter > 0);
}

void henryInterrogation(){ // This function is called whenever Henry is interrogated in the Dining Room
    do {
        printf("\n1. Where were you last night?\n2. Do you have any suspicions?\n3. What's your relationship to everyone?\n4. Did you notice anything different?\n5. Goodbye\n");
        if (flag1 && flag1_5){
            printf("6. Ask about the wristwatch\n");
        }
        printf("Enter your choice (1-5%s): ", (flag1 && flag1_5) ? ", 6" : "");
        scanf(" %c", &UserInput16);
        while (getchar() != '\n');
        switch(UserInput16) {
            case '1': 
                printf("\n\033[1;35m'I was in the dining room cleaning after dinner. Dinner was around 7:00 pm, and the family finished eating at around 8:00.\nI was then bringing the dishes to the kitchen and cleaning the dining room. I finished at aroud 8:45 and retired to my quarters.'\033[0m\n\n");
                decreaseActionMeter();
                printActionMeter();
                break;
            case '2':
                printf("\n\033[1;35m'I do not. If I may give my opinion, I could never believe that anyone occupying the manor would do such a thing.'\033[0m\n\n");
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\033[1;35m'I am on good terms with everyone here in the manor.\nIf I may, Miss Victoria doesn't deserve the treatment her family gives. She is an amazing young woman who followed her dreams. How can anyone fault her for that?'\033[0m\n\n");
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\033[1;35m'Well, I wouldn't really call it suspicious, but I did end up breaking a few dishes yesterday.\nIt was purely on accident as I was cleaning after supper, and I threw the porcelein shards in the trash can in the kitchen. That was around 8:30 pm. Apologies for any confusion.\nOh, It also seems I have misplaced my wristwatch. If you see it, please let me know.'\033[0m\n\n");
                flag1 = 1;
                flag2 = 1;
                if (flag2_5){
                    enter();
                    printf("\033[94mHenry must be talking about the porcelain shards I found in the kitchen garbage can.\033[0m\n\n");
                    enter();
                }
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\033[1;35m'Please, Detective White, find the vagrant who stole the Ruby. The family is depending on you.'\033[0m\n\n");
                break;
            case '6':
                if (flag1 && flag1_5) {
                    printf("\n\033[1;35mYou found my watch!\nYou say it was in the ballroom? Well I can confidently say I never went to the ballroom yesterday. I was in the dining room and kitchen the entire day.\nAsk Loretta! She was talking to me during my time in the kitchen.\033[0m\n\n");
                    decreaseActionMeter();
                    printActionMeter();
                } else {
                    printf("\n\nInvalid option! Please enter a number from 1 to 5.\n");
                }
                break;
            default: 
                printf("\n\nInvalid option! Please enter a number from 1 to 5.\n");
        }
    } while (UserInput16 != '5' && actionMeter > 0);
}

void deborahInterrogation(){ // This function is called whenever Deborah is interrogated in the Gardens
    do {
        printf("\n1. Where were you last night?\n2. Do you have any suspicions?\n3. What's your relationship to everyone?\n4. Did you notice anything different?\n5. Goodbye\n");
        printf("Enter your choice (1-5): ");
        scanf(" %c", &UserInput17);
        while (getchar() != '\n');
        switch(UserInput17) {
            case '1': 
                printf("\n\033[1;33m'Hmmmm, well I was in the conservatory from 10:00pm to 10:45pm taking care of the plants. However, after hearing some glass shattering around 10:45, I thought I saw something outside the conservatory windows,\nso I went outside to the gardens to investigate. That was around 11:00pm. After realizing how dark it was outside and how I was unable to spot anything,\n,I headed back inside around 11:15pm. I then went to bed.'\033[0m\n\n");
                flag3 = 1;
                if((flag3 || flag4_5) && (flag3_5 || flag4)){
                    enter();
                    printf("\033[94m\n\nThis explains what Evelyn saw the night of the incident.\033[0m\n\n");
                    enter();
                }
                decreaseActionMeter();
                printActionMeter();
                break;
            case '2':
                printf("\n\033[1;33m'Just between you and me sweetie, I don't trust Loretta. If you ask me, she's been talking a little too much with Edward, and if you ask me, something is going on.'\033[0m\n\n");
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\033[1;33m'Oh! Well I wasn't expecting this question. I don't have any difficulties with anyone, staff or not. They all treat me with kindness as I do to them.'\033[0m\n\n");
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\033[1;33m'When I was in the conservatory, around 10:45pm I thought I saw a figure skulking in the gardens.\nThere was a bit of glass shattering before that moment so I went to investigate. However, I couldn't find anything. Might have been a ghost. I hear the manor is haunted.'\033[0m\n\n");
                flag4_5 = 1;
                if((flag3 || flag4_5) && flag3_5){
                    enter();
                    printf("\033[94m\n\nThis explains what Evelyn saw the night of the incident.\033[0m\n\n");
                    enter();
                } else if (flag3_5 && flag4 && (flag3 || flag4_5)){
                    enter();
                    printf("\033[94m\n\nThis explains what Evelyn and Victoria saw the night of the incident.\033[0m\n\n");
                    enter();
                }
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\033[1;33m'If you need anything else sweetie, please, do tell me. I will do my best to assist you.'\033[0m\n\n");
                break;
            default: 
                printf("\n\nInvalid option! Please enter a number from 1 to 5.\n");
        }
    } while (UserInput17 != '5' && actionMeter > 0);
}

void lorettaInterrogation(){ // This function is called whenever Loretta is interrogated in the Guest Room
    do {
        printf("\n1. Where were you last night?\n2. Do you have any suspicions?\n3. What's your relationship to everyone?\n4. Did you notice anything different?\n5. Goodbye\n");
        printf("Enter your choice (1-5): ");
        scanf(" %c", &UserInput18);
        while (getchar() != '\n');
        switch(UserInput18) {
            case '1': 
                printf("\n\033[1;32m'Being perfectly honest detective, I was cleaning the entire manor. I was going room to room tidying up.\nI honestly can't remember when I entered which room, but I'm positive the others may remember me entering rooms that they were lounging in.'\nI did notice however, that Edward left at around 6:30pm to head to the Ravenwood Casino and Jacob left for his second job at 7:00pm.\033[0m\n\n");
                flag5 = 1;
                if (flag5 && flag5_5 && flag5_75){
                    enter();
                    printf("\033[94mIt sounds like Edward, Henry, and Loretta's alibis all hold true with each other.\033[0m\n\n");                   
                    enter();
                } else if (flag5 && flag5_75){
                    enter();
                    printf("\033[94m]This corroberates Edwards's claim about where he went last night.\033[0m\n\n");
                    enter();
                } else if (flag5_5 && flag5){
                    enter();
                    printf("\033[94mThis corroberates Henry's claim about where he went last night.\033[0m\n\n");
                    enter();
                }
                decreaseActionMeter();
                printActionMeter();
                break;
            case '2':
                printf("\n\033[1;32m'If I may, Jacob isn't the most...stable in of the staff. Between you and I, there is no way that he doesn't have a motive for the theft.\nIf you want to see what I'm implying, try talking to him. I'm sure Edward would agree with me when I say that something isn't right with him.'\033[0m\n\n");
                flag6 = 1;
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\033[1;32m'Well, being the housekeeper allows me to move around the manor to clean. Because of that, I usually chat with the staff and family members as I come across them.\nI am on friendly terms with everyone as a result. It would be awkward otherwise as I couldn't avoid them.'\033[0m\n\n");
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\033[1;32m'Well at around 10:45pm, I was in the guest room with Evelyn and Victoria as I was cleaning the area. However, I thought I heard a sound, but very faintly.\nI was searching the area along with Victoria and Evelyn, but nothing came up.'\033[0m\n\n");
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\033[1;32m'I wish you the best, Detective!'\033[0m\n\n");
                break;
            default: 
                printf("\n\nInvalid option! Please enter a number from 1 to 5.\n");
        }
    } while (UserInput18 != '5' && actionMeter > 0);
}

void jacobInterrogation(){ // This function is called whenever Jacob is interrogated in the kitchen.
    do {
        printf("\n1. Where were you last night?\n2. Do you have any suspicions?\n3. What's your relationship to everyone?\n4. Did you notice anything different?\n5. Goodbye\n");
        printf("Enter your choice (1-5): ");
        scanf(" %c", &UserInput19);
        while (getchar() != '\n');
        switch(UserInput19) {
            case '1': 
                printf("\n\033[1;31m'If you must know, I was preparing dinner in the kitchen from 5:00pm to 6:30pm. Henry then came to serve supper to the guests at 7:00pm.\nFor the rest of the evening, I wasn't here, as I have a second job I go to overnight.\nSo at 7:00pm sharp, I got in my car and drove away.'\033[0m\n\n");
                flag5_5 = 1;
                if (flag5 && flag5_5){
                    enter();
                    printf("\033[94m]This corroberates Loretta's claim about where Henry went last night.\033[0m");
                    enter();
                }
                decreaseActionMeter();
                printActionMeter();
                break;
            case '2':
                printf("\n\033[1;31m'I don't know, and I don't care.'\033[0m\n\n");
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\033[1;31m'I come here to do my job and leave. I'm not interested in building connections.\nReginald doesn't like me, but I'm the only cook that can make anything worth a damn that's not farther than 50 miles away.'\033[0m\n\n");
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\033[1;31m'Did you even hear me? I said I wasn't here.'\033[0m\n\n");
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\033[1;31m'Don't bother me again, or it will be the last time you ever do.'\033[0m\n\n");
                break;
            default: 
                printf("\n\nInvalid option! Please enter a number from 1 to 5.\n");
        }
    } while (UserInput19 != '5' && actionMeter > 0);
}

void entranceHall(){ // This function is called whenever the user enters the entrance hall
    printf("\n\033[90mYou walk into the entrance hall and are greeted by the Pembroke family members!\n\033[0m\n");
    do {
        printf("\033[91mTo whom would you like to approach?\033[0m\n\n");
        printf("1. Sir Reginald Pembroke\n2. Lady Evelyn Pembroke\n3. Lord Edward Pembroke\n4. Miss Victoria Pembroke\n");
        printf("Enter 1, 2, 3, or 4 to talk to someone! If you don't feel like talking to anyone, press 0: ");
        scanf(" %c", &UserInput2);
        while (getchar() != '\n');
        switch (UserInput2) {
            case '1':
                printf("\033[90m\nYou decide to walk up to Reginald Pembroke\n\033[0m");
                enter();
                printf("\033[0;33m'Hello, Detective White. I am Reginald Pembroke, the head of the Pembroke Family.\n Is there anything you would like to know?'\033[0m\n\n");
                familyDialogue();
                break;
            case '2':
                printf("\033[90m\nYou decide to walk up to Evelyn Pembroke\n\033[0m");
                enter();
                printf("\033[0;91;95m'My, My, what a dashing young man you are Mister White. How might I be able to assist you in your search for the Ruby?'\033[0m\n\n");
                familyDialogue();
                break;
            case '3':
                printf("\033[90m\nYou decide to walk up to Edward Pembroke\n\033[0m");
                enter();
                printf("\033[32m'My God... It's a pleasure to finally meet the famous Benjamin White! I'll tell you anything you need to crack this case!'\033[0m\n\n");
                familyDialogue();
                break;
            case '4':
                printf("\033[90m\nYou decide to walk up to Victoria Pembroke\n\033[0m");
                enter();
                printf("\033[0;34m'Hello, detective. Are you the one who's going to solve which of my family members stole the Ruby?'\033[0m\n\n");
                familyDialogue();
                break;
            case '0':
                printf("\033[90m\nYou decide to investigate somewhere else.\n\033[0m");
                enter();
                break;
            default:
                printf("\nInvalid option!\n");
                enter();
        }
    } while (UserInput2 != '0' && actionMeter > 0);
}

void ballroom(){ // All of the Ballroom's investgation opportunities
    do{
        UserInput6 = 0;
        printf("\n\033[91mWhat would you like to investigate?\033[0m\n\n");
        printf("1. Lockers\n2. Dance floor \n3. Sound System\n4. Chandelier\n5. I'm done investigating\n");
        scanf(" %c", &UserInput6);
        while (getchar() != '\n');
        switch (UserInput6){
            case '1':
                printf("\n\n\033[90mYou walk over the Ballroom's lockers.\033[0m\n\n");
                enter();
                printf("It looks like the ballroom contains a few lockers against its walls to store supplies and personal belongings.\nHowever, it looks like every locker but one is closed.\n\n");
                enter();
                printf("As you take a closer look at the open locker, you can see a dusty handprint on the inside of the locker door.\nIt seems that someone hid inside of this locker at some point.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '2':
                printf("\n\n\033[90mYou do a sweep of the Ballroom's main dance floor.\033[0m\n\n");
                enter();
                printf("The ballroom's floor is clear of debris or mess. It seems it was cleaned recently.\nNothing else is out of the ordinary.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\n\033[90mYou decide to investgate the Ballroom's sound system.\033[0m\n\n");
                enter();
                printf("The ballroom contains a sound system to play music at events such as parties and balls.\nTaking a closer look, it seems the sound system hasn't been tampered with. However there is something on the ground.\nLooking a little closer shows a wristwatch right beside the sound system.\n\n");
                flag1_5 = 1;
                if(flag1){
                    enter();
                    printf("\033[94mThis must be the wristwatch Henry was saying went missing.\033[0m\n\n");
                    enter();
                }
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\n\033[90mYou look up at the Ballroom's chandelier.\033[0m\n\n");
                enter();
                printf("There is an extravagent chandelier hanging above the ballroom. You look up in awe.\n\n");
                enter();
                printf("It is encrusted in jewels and gemstones, showing the testament of wealth the Pembroke family holds.\nNot much else to investigate other than that it seems.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\n\033[90mSatisfied with your findings, you head back to the entrance of the area\033[0m\n\n");
                enter();
                investigateOrLeave();
                break;
            default:
                printf("\n\nInvalid Input! Please enter 1-5.\n");
        }
    } while (UserInput6 != '5' && actionMeter > 0);
}

void diningRoom(){ // All of the Dining Room's investigation events
    do{
        UserInput7 = 0;
        printf("\n\033[91mWhat would you like to investigate?\033[0m\n\n");
        printf("1. Interrogate Henry\n2. Dining Room Table\n3. Trash\n4. Paintings\n5. I'm done investigating\n");
        scanf(" %c", &UserInput7);
        while (getchar() != '\n');
        switch (UserInput7){
            case '1':
                printf("\n\n\033[90mYou walk up to Henry, hoping to gain some information.\033[0m\n\n");
                enter();
                printf("\033[1;35m'Ah, I hope your investigation is going well, Mr. White. I'm currently cleaning up this morning's meal. Is there anything you'd like to know?'\033[0m\n\n");
                henryInterrogation();
                break;
            case '2':
                printf("\n\n\033[90mYou decide to scan the dining room table.\033[0m\n\n");
                enter();
                printf("It appears to be cleaned recently. It seems the Pembroke family recently ate breakfast.\nDespite the cleanliness, there are a few porcelain dishes still lying on the table.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\n\033[90mYou take a peek inside the dining room's trash can.\033[0m\n\n");
                enter();
                printf("This trash can seems to have been emptied recently. There is nothing of note inside.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\n\033[90mYou take a second to admire the paintings on the walls.\033[0m\n\n");
                enter();
                printf("There are 4 different paintings hanging on the wall. The first is a painting done of the exterior of the Pembroke Manor.\nThe second is what appears to be a family portrait of the previous owners of the Pembroke Manor with the third being a portrait of the current Pembroke family beside it.\nThe final portrait is of a singular person. It is signed Sir Taven Pembroke.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\n\033[90mSatisfied with your findings, you head back to the entrance of the area.\033[0m\n\n");
                enter();
                investigateOrLeave();
                break;
            default:
                printf("\n\nInvalid Input! Please enter 1-5.\n");
        }
    } while (UserInput7 != '5' && actionMeter > 0);
}

void library(){ // All of the Library's investigation events
    do{
        UserInput8 = 0;
        printf("\n\033[91mWhat would you like to investigate?\033[0m\n\n");
        printf("1. Bookshelves\n2. Laptop\n3. Coffee Mug\n4. Desk Drawers\n5. I'm done investigating\n");
        scanf(" %c", &UserInput8);
        while (getchar() != '\n');
        switch (UserInput8){
            case '1':
                printf("\n\n\033[90mYou scroll the books on the bookshelves.\033[0m\n\n");
                enter();
                printf("There are encyclopedias, files, and other books sitting along the bookshelf. It looks like a very expensive collection to say the least.\nIt doesn't look like there are any clues on the bookshelf.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '2':
                printf("\n\n\033[90mYou notice a laptop laying nearby. You turn it on and look inside.\033[0m\n\n");
                enter();
                printf("It appears there is nothing of note after browsing the files of the computer.\nI think the creator of this laptop proabbly didn't have enough time to implement a functioning laptop section of this game.\nWait, what game?");
                enter();
                decreaseActionMeter(); 
                printActionMeter();
                break;
            case '3':
                printf("\n\n\033[90mYou notice a Coffee Mug on top of a desk nearby.\033[0m\n\n");
                enter();
                printf("The coffee mug itself doesn't look like anything special.\nIt isn't filled, but there are clear traces of coffee being inside not too long ago.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\n\033[90mYou open the desk drawers in the library.\033[0m\n\n");
                enter();
                printf("Looking inside the desk drawer, you spot a piece of parchment paper. Investigating further, you read the contents.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\n\033[90mSatisfied with your findings, you head back to the entrance of the area.\033[0m\n\n");
                enter();
                investigateOrLeave();
                break;
            default:
                printf("\n\nInvalid Input! Please enter 1-5.\n");
        }
    } while (UserInput8 != '5' && actionMeter > 0);
}

void kitchen(){ // All of the Kitchen's investigation events
    do{
        UserInput9 = 0;
        printf("\n\033[91mWhat would you like to investigate?\033[0m\n\n");
        printf("1. Interrogate Jacob\n2. Kitchen Counter\n3. Kitchen Knives\n4. Trash Can\n5. I'm done investigating\n");
        scanf(" %c", &UserInput9);
        while (getchar() != '\n');
        switch (UserInput9){
            case '1':
                printf("\n\n\033[90mYou walk up to Jacob, hoping to find more clues.\033[0m\n\n");
                enter();
                printf("\n\n\033[1;31m'God, I was hoping you'd leave me alone...'\n\n\033[0m");
                jacobInterrogation();
                break;
            case '2':
                printf("\n\n\033[90mYou scan the kitchen counter.\033[0m\n\n");
                enter();
                printf("The kitchen counter doesn't seem to have been cleaned recently. It seems the cook is still cleaning from breakfast.\nThere are a few dishes and cups laying about.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\n\033[90mCurisously, you take a look at the knife rack.\033[0m\n\n");
                enter();
                printf("Thankfully, as it seems, there are no missing knives from the knife rack. The knives don't seem to be a part of this case.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\n\033[90mYou glance inside the trash can in the kitchen.\033[0m\n\n");
                enter();
                printf("Curiously, you find broken pieces of porcelain inside the trash can.\n\n");
                enter();
                flag2_5 = 1;
                if (flag2 && flag2_5){
                    enter();
                    printf("\033[94mThis must be the shards of porcelain Henry was talking about from the dish he broke.\033[0m\n\n");
                    enter();
                }
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\n\033[90mSatisfied with your findings, you head back to the entrance of the area.\033[0m\n\n");
                enter();
                investigateOrLeave();
                break;
            default:
                printf("\n\nInvalid Input! Please enter 1-5.\n");
        }
    } while (UserInput9 != '5' && actionMeter > 0);
}

void guestRoom(){ // All of the Guest Room's investigation events
    do{
        UserInput10 = 0;
        printf("\n\033[91mWhat would you like to investigate?\033[0m\n\n");
        printf("1. Interrogate Loretta\n2. Window\n3. Look under couch\n4. Investigate surroundings\n5. I'm done investigating\n");
        scanf(" %c", &UserInput10);
        while (getchar() != '\n');
        switch (UserInput10){
            case '1':
                printf("\n\n\033[90mHoping to find some answers, you walk up to Loretta.\033[0m\n\n");
                enter();
                printf("\n\n\033[1;32m'You've arrived, I see. I hope the manor is to your liking; I take pride in its cleanliness.'\033[0m\n\n");
                lorettaInterrogation();
                break;
            case '2':
                printf("\n\n\033[90mYou take a look out the guest room window.\033[0m\n\n");
                enter();
                printf("Outside the window, you see a clear view of the gardens.\nBeyond the gardens is the Pembroke Manor Lake, as well as the main road leading towards the city.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\n\033[90mThouroughly, you check underneath the sofa.\033[0m\n\n");
                enter();
                printf("It doesn't seem like there is anything under the couch. It looks cleaned recently.\nMight have been too obvious of a place to find clues.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\n\033[90mYou take a look around the guest room, finding inconsitencies.\033[0m\n\n");
                enter();
                printf("The study room, the scene of the crime is next to the guest room. If anyone was in the guest room at the time of the crime, why was nothing heard?\nEven then, if something was heard, why did no one investigate the study room to check?\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\n\033[90mSatisfied with your findings, you head back to the entrance of the area.\033[0m\n\n");
                enter();
                investigateOrLeave();
                break;
            default:
                printf("\n\nInvalid Input! Please enter 1-5.\n");
        }
    } while (UserInput10 != '5' && actionMeter > 0);
}

void study(){ // All of the Study's investigation events
    do{
        UserInput11 = 0;
        printf("\n\033[91mWhat would you like to investigate?\033[0m\n\n");
        printf("1. Study Desk Drawers\n2. Search for Belongings\n3. Broken Display Case\n4. Shoeprints\n5. I'm done investigating\n");
        scanf(" %c", &UserInput11);
        while (getchar() != '\n');
        switch (UserInput11){
            case '1':
                printf("\n\n\033[90mYou check inside the drawers of the desk in the room.\033[0m\n\n");
                enter();
                printf("The only things inside the drawers are papers. They detail the Ruby's value from an appraial, valuing at 1.3 million dollars.\nThere is no way a family heirloom like this was going to be sold. Though clearly the culprit was looking to make some money.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '2':
                printf("\n\n\033[90mIn hopes of finding clues to the culprit, you search for anything left behind.\033[0m\n");
                enter();
                printf("The culprit seemed quite thorough. The only thing left behind is a gardening shovel, more than likely used to break the glass. You wonder where this came from.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\n\033[90mYou walk up to the shattered display case.\033[0m\n\n");
                enter();
                printf("This is where the Ravenwood Ruby was originally kept. The Ruby is gone, with shattered glass laying around the floor.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\n\033[90mLooking at the floor, you spot shoeprints and investigate them.\033[0m\n\n");
                enter();
                printf("There are bootprints leading from outside to the broken display case, which held the ruby. The culprit must have been outside before the theft took place.\nThere appears to be footprints leading back outside towards the entrance hall, leading to the garden as well.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\n\033[90mSatisfied with your findings, you head back to the entrance of the area\033[0m\n\n");
                enter();
                investigateOrLeave();
                break;
            default:
                printf("\n\nInvalid Input! Please enter 1-5.\n");
        }
    } while (UserInput11 != '5' && actionMeter > 0);
     
}

void conservatory(){ // All of the Conservatory investigation events
    do{
        UserInput12 = 0;
        printf("\n\033[91mWhat would you like to investigate?\033[0m\n\n");
        printf("1. Windows\n2. Plants\n3. Lighting\n4. Book\n5. I'm done investigating\n");
        scanf(" %c", &UserInput12);
        while (getchar() != '\n');
        switch (UserInput12){
            case '1':
                printf("\n\n\033[90mDeciding to take in the surroundings, you look out the conservatory's windows.\033[0m\n\n");
                enter();
                printf("Looking out the window, you can see parts of the gardens outside, and a perfect view of the Pembroke Lake.\nThis seems like a relaxing spot to unwind.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '2':
                printf("\n\n\033[90mYou admire the plants that are growing in the conservatory.\033[0m\n\n");
                enter();
                printf("The conservatory holds a wide variety of plants throughout. Tulips, lillies, chrysanthemums, and other flowers are blooming.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\n\033[90mYou notice the fluorescent lighting above te conservatory.\033[0m\n\n");
                enter();
                printf("The conservatory usually uses natural light from outside as lighting.\nHowever, it looks like there are lights hanging above the conservatory for nighttime when the sun sets. They appear to be turned off right now.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\n\033[90mIt looks like someone was reading. You investigate the book.\033[0m\n\n");
                enter();
                printf("The book is titled The Pembroke Family Conspiracy. You skim through the introduction of the book, gathering the gist of the book.\n\n");
                enter();
                printf("It appears that Taven Pembroke, the previous generation's Pembroke family head, murdered his family in an attempt to sell the family fortune.\nHowever, Taven mysteriously dissappeared before the family fortune was able to be acquired.\nTaven has not discovered since then, leaving behind a haunted Pembroke Manor to be occpied by Taven's brother, Reginald Pembroke.\n\n");
                enter();
                printf("\033[90mThis book explains the hauntings of the Pembroke Family Manor. You wonder if it has any standing on the case.\033[0m\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\n\033[90mSatisfied with your findings, you head back to the entrance of the area.\033[0m\n\n");
                enter();
                investigateOrLeave();
                break;
            default:
                printf("\n\nInvalid Input! Please enter 1-5.\n");
        }
    } while (UserInput12 != '5' && actionMeter > 0);
}

void hallway(){  // All of the Hallway's investigation events
    do{
        UserInput13 = 0;
        printf("\n\033[91mWhat would you like to investigate?\033[0m\n\n");
        printf("1. Check the flooring\n2. Family Pictures\n3. Display cases\n4. Previous Owner's Mural\n5. I'm done investigating\n");
        scanf(" %c", &UserInput13);
        while (getchar() != '\n');
        switch (UserInput13){
            case '1':
                printf("\n\n\033[90mYou notice the wood panel flooring, checking if there are any loose panels.\033[0m\n\n");
                enter();
                printf("Scanning the floor and testing the panels, you come to the conclusion that there is nothing of note with the wooden panels. None of them seem loose.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '2':
                printf("\n\n\033[90mYou look upon the Pembroke family pictures on the walls.\033[0m\n\n");
                enter();
                printf("In front of the manor, a young Victoria and Edward Pembroke stand side by side, clearly not wanting to be in the picture.\nBehind Edward is Evelyn Pembroke, whom is leaning on Reginald Pembroke's arm.\nReginald, standing behind Victoria, looks into the camera with an authoritative, yet pleased smile.\nCould one of these people have stole the ruby?\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\n\033[90mYou scan the hallway's display cases filled with medals and awards.\033[0m\n\n");
                enter();
                printf("Most of them have Edward Pembroke's name on them.\n'Ravenwood Raptors Nationals Fencing Cup Finals 2007', 'Valedictorian Ravenwood High 2008', 'Ravenwood Business Journal CFO Award'.\nVictoria's name doesn't appear on any of the awards.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\n\033[90mYou look at a mural of the manor's previous occupants.\033[0m\n\n");
                enter();
                printf("The mural shows a family of five. One man, one woman, and three children. There appears to be a plaque below the mural:\nIn loving memory: Taven Pembroke and Michelle Pembroke, along with their children Rocco Pembroke, Gabriella Pembroke, and Shelby Pembroke.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\n\033[90mSatisfied with your findings, you head back to the entrance of the area\033[0m\n\n");
                enter();
                investigateOrLeave();
                break;
            default:
                printf("\n\nInvalid Input! Please enter 1-5.\n");
        }
    } while (UserInput13 != '5' && actionMeter > 0);
    
}

void gardens(){  // All of the Garden's investigation events
    do{
        UserInput14 = 0;
        printf("\n\033[91mWhat would you like to investigate?\033[0m\n\n");
        printf("1. Interrogate Deborah\n2. Shoeprints\n3. Main Road\n4. Historical Infopost\n5. I'm done investigating\n");
        scanf(" %c", &UserInput14);
        while (getchar() != '\n');
        switch (UserInput14){
            case '1':
                printf("\n\n\033[90mNoticing the gardner plant some flowers, you decide to ask Deborah a few questions.\033[0m\n\n");
                enter();
                printf("\n\n'\033[1;33mMy, you've caught me at a terrible time, please forgive me. I was just tending to the flowers. What do you need, dearie?'\033[0m\n\n");
                deborahInterrogation();
                break;
            case '2':
                printf("\n\n\033[90mYou notice some shoeprints inside the garden.\033[0m\n\n");
                enter();
                printf("There are shoeprints in the garden leading into the entrance hall of the manor. It appears the path goes further back to the lake.\nIt also looks like there are shoeprints coming out of the entrance hall and leading towards the main road.\n\n");
                enter();
                printf("In other words, someone came from the lake, entered the manor through the entrance hall, and later, left the manor, heading to the main road.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\n\033[90mYou walk up to the main road that connects to the garden.\033[0m\n\n");
                enter();
                printf("This is the main road that leads towards the city. The road only goes in that direction, away from the Pembroke property.\nIt appears someone who isn't a Pembroke family member cannot gain access to the property or the lake because of the road.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\n\033[90mCurious about the manor's past, you check the infopost in the gardens.\033[0m\n\n");
                enter();
                printf("The infopost seems to explain the history of the manor's ownership:\n'The Pembroke Family manor is passed down from generation to generation once the patriarch is deceased.\nThe manor was built several generations ago, and with upkeep from trusted staff members, hired through the family, the manor is as pristine as when it was first built.'\n\n");
                enter();
                printf("It appears the manor has significane with the Pembroke family. You wonder about the previous generations of the family.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\n\033[90mSatisfied with your findings, you head back to the entrance of the area.\033[0m\n\n");
                enter();
                investigateOrLeave();
                
                break;
            default:
                printf("\n\nInvalid Input! Please enter 1-5.\n");
        }
    } while (UserInput14 != '5' && actionMeter > 0);
    
}

void lake(){ // All of the Lake's investigation events
    do{
        UserInput15 = 0;
        printf("\n\033[91mWhat would you like to investigate?\033[0m\n\n");
        printf("1. Shoeprints\n2. Warning Sign\n3. Shed\n4. Lake\n5. I'm done investigating\n");
        scanf(" %c", &UserInput15);
        while (getchar() != '\n');
        switch (UserInput15){
            case '1':
                printf("\n\n\033[90mYou notice shoeprints at the lake. You take a look a them.\033[0m\n\n");
                enter();
                printf("The shoeprints at the lake seem to start from the lake shed. After that, they seem to go straight towards the Pembroke Manor Gardens.\nWhy are these shoeprints here?\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '2':
                printf("\n\n\033[90mYou see a 'Do not Swim' sign. You investigate it.\033[0m\n\n");
                enter();
                printf("You wonder as to why the Pembroke Lake isn't allowed to be swam in. You look into the lake and spot a few fish swimming about.\nIt appears the sign is there to protect wildlife.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '3':
                printf("\n\n\033[90mCuriously, you open the shed and check inside.\033[0m\n\n");
                enter();
                printf("Inside the shed you notice a few things.\nFirstly, there are gardening supplies hanging along the walls of the shed. Shovels, spades, rakes, and more are just some of the tools inside.\n\n");
                enter();
                printf("Secondly, there appears to be snack wrappers on the floor of the shed, along with a stool.\nIt looks like someone was inside this shed at some point.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '4':
                printf("\n\n\033[90mJust for a moment, you stop and take in the Pembroke Lake.\033[0m\n\n");
                enter();
                printf("The morning sun glints the water of the lake. There is a fountain in the middle of a lake, with a fancy marble statue as the centerpiece. A few fish are also seen swimming.\n\n");
                enter();
                decreaseActionMeter();
                printActionMeter();
                break;
            case '5':
                printf("\n\n\033[90mSatisfied with your findings, you head back to the entrance of the area.\033[0m\n\n");
                enter();
                investigateOrLeave();
                break;
            default:
                printf("\n\nInvalid Input! Please enter 1-5.\n");
        }
    } while (UserInput15 != '5' && actionMeter > 0);
}

void investigateOrLeave(){ // Player decides to  either investigate the room or explore other areas of the manor
    UserInput5 = 0;
    printf("\033[91m\nWould you like to investigate the area or continue walking?\033[0m\n\n");
    printf("1. Investigate\n2. Go somewhere else\n");
    scanf(" %c", &UserInput5);
    while (getchar() != '\n');
    while (UserInput5 != '1' && UserInput5 != '2') {
        printf("Invalid input! Please enter 1 or 2: \n");
        scanf(" %c", &UserInput5);
        while (getchar() != '\n');
    } 
    if (UserInput5 == '1') {
        printf("\033[90m\nYou decide to investigate the area.\n\n\033[0m");
        enter();
        switch(currentRoom){
            case BALLROOM:
                ballroom();
                break;
            case ENTRANCE_HALL:
                entranceHall();
                break;
            case DINING_ROOM:
                diningRoom();
                break;
            case LIBRARY:
                library();
                break;
            case KITCHEN:
                kitchen();
                break;
            case GUEST_ROOM:
                guestRoom();
                break;
            case STUDY:
                study();
                break;
            case CONSERVATORY:
                conservatory();
                break;
            case HALLWAY:
                hallway();
                break;
            case GARDENS:
                gardens();
                break;
            case LAKE:
                lake();
                break;
        }
    } else if (UserInput5 == '2') {
        printf("\033[90m\nYou decide there is somewhere else you need to go.\n\n\033[0m");
        enter();
        roomChangeSelection();
    }
}

void roomChangeLibrary(enum Room room){ // Whenever the user moves to a different room, a message is displayed, as well as that room's function
    currentRoom = room;
    switch (currentRoom) {
            case ENTRANCE_HALL:
                printf("\033[90m\nYou walk to the entrance hall.\n\n\033[0m");
                enter();
                investigateOrLeave();
                break;
            case BALLROOM:
                printf("\033[90m\nYou walk to the ballroom.\n\n\033[0m");
                enter();
                investigateOrLeave();
                break;
            case DINING_ROOM:
                printf("\033[90m\nYou walk to the dining room.\n\n\033[0m");
                enter();
                investigateOrLeave();
                break;
            case LIBRARY:
                printf("\033[90m\nYou walk to the library.\n\n\033[0m");
                enter();
                investigateOrLeave();
                break;
            case KITCHEN:
                printf("\033[90m\nYou walk to the kitchen.\n\n\033[0m");
                enter();
                investigateOrLeave();
                break;
            case GUEST_ROOM:
                printf("\033[90m\nYou walk to the guest room.\n\n\033[0m");
                enter();
                investigateOrLeave();
                break;
            case STUDY:
                printf("\033[90m\nYou walk to the study.\n\n\033[0m");
                enter();
                investigateOrLeave();
                break;
            case CONSERVATORY:
                printf("\033[90m\nYou walk to the conservatory.\n\n\033[0m");
                enter();
                investigateOrLeave();
                break;
            case HALLWAY:
                printf("\033[90m\nYou walk to the hallway.\n\n\033[0m");
                enter();
                investigateOrLeave();
                break;
            case GARDENS:
                printf("\033[90m\nYou walk to the gardens.\n\n\033[0m");
                enter();
                investigateOrLeave();
                break;
            case LAKE:
                printf("\033[90m\nYou walk to the lake.\n\n\033[0m");
                enter();
                investigateOrLeave();
                break;
            default:
                printf("\033[91m\nYou have broken the game...\n\n\033[0m");
        }
}

void roomChangeSelection(){ // This is a selection of rooms that are possible to move to based off of current room. This is also very extensive
    int UserInput4 = 0; // Initializes UserInput 4 as 0 every time the user wants to change a room.
    printf("\033[91m\nWhere would you like to go?\033[0m\n\n");
    if (currentRoom == ENTRANCE_HALL){
        do {
            printf("1. The Library\n2. The Study\n3. The Hallway\n4. The Gardens\n5. Go Back\n");
            scanf(" %d", &UserInput4);
            while (getchar() != '\n');
            switch(UserInput4){
                case 1:
                    roomChangeLibrary(LIBRARY);
                    break;
                case 2:
                    roomChangeLibrary(STUDY);
                    break;
                case 3:
                    roomChangeLibrary(HALLWAY);
                    break;
                case 4:
                    roomChangeLibrary(GARDENS);
                    break;
                case 5:
                    roomChangeLibrary(ENTRANCE_HALL);
                    break;
                default:
                    printf("\n\nInvalid Input! Try again.\n\n");
            }        
        } while (UserInput4 != 1 && UserInput4 !=2 && UserInput4 != 3 && UserInput4 !=4 && UserInput4 != 5);
        
    } else if (currentRoom == BALLROOM){
        do {
            printf("1. The Kitchen\n2. The Library\n3. Go Back\n");
            scanf(" %d", &UserInput4);
            while (getchar() != '\n');
            switch(UserInput4){
                case 1:
                    roomChangeLibrary(KITCHEN);
                    break;
                case 2:
                    roomChangeLibrary(LIBRARY);
                    break;
                case 3:
                    roomChangeLibrary(BALLROOM);
                    break;
                default:
                    printf("\n\nInvalid Input! Try again.\n\n");
            }
        } while (UserInput4 != 1 && UserInput4 !=2 && UserInput4 != 3);
        
    } else if(currentRoom == DINING_ROOM){
        do{
            printf("1. The Kitchen\n2. The Guest Room\n3. The Study\n4. The Library\n5. Go Back\n");
            scanf(" %d", &UserInput4);
            while (getchar() != '\n');
            switch(UserInput4){
                case 1:
                    roomChangeLibrary(KITCHEN);
                    break;
                case 2:
                    roomChangeLibrary(GUEST_ROOM);
                    break;
                case 3:
                    roomChangeLibrary(STUDY);
                    break;
                case 4:
                    roomChangeLibrary(LIBRARY);
                    break;
                case 5:
                    roomChangeLibrary(DINING_ROOM);
                    break;
                default:
                    printf("\n\nInvalid Input! Try again.\n\n");
            }
        } while (UserInput4 != 1 && UserInput4 !=2 && UserInput4 != 3 && UserInput4 !=4 && UserInput4 != 5);
    } else if (currentRoom == LIBRARY){
        do{
            printf("1. The Ballroom\n2. The Dining Room\n3. The Entrance Hall\n4. Go Back\n"); 
            scanf(" %d", &UserInput4);   
            while (getchar() != '\n');
            switch(UserInput4){
                case 1:
                    roomChangeLibrary(BALLROOM);
                    break;
                case 2:
                    roomChangeLibrary(DINING_ROOM);
                    break;
                case 3:
                    roomChangeLibrary(ENTRANCE_HALL);
                    break;
                case 4:
                    roomChangeLibrary(LIBRARY);
                    break;
                default:
                    printf("\n\nInvalid Input! Try again.\n\n");
            }            
        } while (UserInput4 != 1 && UserInput4 !=2 && UserInput4 != 3 && UserInput4 !=4);
    } else if (currentRoom == KITCHEN){
        do{
            printf("1. The Ballroom\n2. The Dining Room\n3. Go Back\n");
            scanf(" %d", &UserInput4);
            while (getchar() != '\n');
            switch(UserInput4){
                case 1:
                    roomChangeLibrary(BALLROOM);
                    break;
                case 2:
                    roomChangeLibrary(DINING_ROOM);
                case 3:
                    roomChangeLibrary(KITCHEN);
                    break;
                default:
                    printf("\n\nInvalid Input! Try again.\n\n");
            }  
        } while (UserInput4 != 1 && UserInput4 !=2 && UserInput4 != 3);  
    } else if (currentRoom == GUEST_ROOM){
        do {
            printf("1. The Dining Room\n2. The Study\n3. The Conservatory\n4. Go Back\n");
            scanf(" %d", &UserInput4);
            while (getchar() != '\n');
            switch(UserInput4){
                case 1:
                    roomChangeLibrary(DINING_ROOM);
                    break;
                case 2:
                    roomChangeLibrary(STUDY);
                    break;
                case 3:
                    roomChangeLibrary(CONSERVATORY);
                    break;
                case 4:
                    roomChangeLibrary(GUEST_ROOM);
                    break;
                default:
                    printf("\n\nInvalid Input! Try again.\n\n");
            }     
        } while (UserInput4 != 1 && UserInput4 !=2 && UserInput4 != 3 && UserInput4 !=4);
    } else if (currentRoom == STUDY){
        do {
            printf("1. The Entrance Hall\n2. The Dining Room\n3. The Conservatory\n4. The Guest Room\n5. Go Back\n");
            scanf(" %d", &UserInput4);
            while (getchar() != '\n');
            switch(UserInput4){
                case 1:
                    roomChangeLibrary(ENTRANCE_HALL);
                    break;
                case 2:
                    roomChangeLibrary(DINING_ROOM);
                    break;
                case 3:
                    roomChangeLibrary(CONSERVATORY);
                    break;
                    case 4:
                    roomChangeLibrary(GUEST_ROOM);
                    break;
                case 5:
                    roomChangeLibrary(STUDY);
                    break;
                default:
                    printf("\n\nInvalid Input! Try again.\n\n");
            }
        } while (UserInput4 != 1 && UserInput4 !=2 && UserInput4 != 3 && UserInput4 !=4 && UserInput4 != 5);
        
    } else if (currentRoom == CONSERVATORY){
        do{
            printf("1. The Hallway\n2. The Study\n3. The Guest Room\n4. Go Back\n");
            scanf(" %d", &UserInput4);
            while (getchar() != '\n');
            switch(UserInput4){
                case 1:
                    roomChangeLibrary(HALLWAY);
                    break;
                case 2:
                    roomChangeLibrary(STUDY);
                    break;
                case 3:
                    roomChangeLibrary(GUEST_ROOM);
                    break;
                case 4:
                    roomChangeLibrary(CONSERVATORY);
                    break;
                default:
                    printf("\n\nInvalid Input! Try again.\n\n");
            }
        } while (UserInput4 != 1 && UserInput4 !=2 && UserInput4 != 3 && UserInput4 !=4);
    } else if (currentRoom == GARDENS){
        do{
            printf("1. The Lake\n2. The Entrance Hall\n3. Go Back\n");
            scanf(" %d", &UserInput4);
            while (getchar() != '\n');
            switch(UserInput4){
                case 1:
                    roomChangeLibrary(LAKE);
                    break;
                case 2:
                    roomChangeLibrary(ENTRANCE_HALL);
                    break;
                case 3:
                    roomChangeLibrary(GARDENS);
                    break;
                default:
                    printf("\n\nInvalid Input! Try again.\n\n");
            }
        } while (UserInput4 != 1 && UserInput4 !=2 && UserInput4 != 3);
    } else if (currentRoom == HALLWAY){
        do {
            printf("1. The Entrance Hall\n2. The Conservatory\n3. Go Back\n");
            scanf(" %d", &UserInput4);
            while (getchar() != '\n');
            switch(UserInput4){
                case 1:
                    roomChangeLibrary(ENTRANCE_HALL);
                    break;
                case 2:
                    roomChangeLibrary(CONSERVATORY);
                    break;
                case 3:
                    roomChangeLibrary(HALLWAY);
                    break;
                default:
                    printf("\n\nInvalid Input! Try again.\n\n");
            }
        } while (UserInput4 != 1 && UserInput4 !=2 && UserInput4 != 3);
    } else {
        do{
            printf("1. The Gardens\n2. Go Back\n");
            scanf(" %d", &UserInput4);
            while (getchar() != '\n');
            switch(UserInput4){
                case 1:
                    roomChangeLibrary(GARDENS);
                    break;
                case 2:
                    roomChangeLibrary(LAKE);
                    break;
                default:
                    printf("\n\nInvalid Input! Try again.\n\n");
            }
        } while (UserInput4 != 1 && UserInput4 !=2);
    }
}

int main() {
    writeFile();
    welcome();
    enter();

    // Case File Intro
    printf("\033[90mYou are about to walk into the Pembroke Manor, when you realize you were handed a case file of the incident back at the station.\n\033[0m\n");
    while (1) { 
        printf("\033[91m\nWould you like to review the case file?\n\n\033[0m");
        printf("Enter Y for yes, or N for no: ");
        scanf(" %c", &UserInput1);
        while (getchar() != '\n');

        if (UserInput1 == 'Y' || UserInput1 == 'y') {
            readFile();
            enter();
            printf("\033[90mYou put the case file away, with newfound information on the case at hand, ready to tackle the mystery of the Ravenwood Ruby.\033[0m\n");
            printf("\033[90mYou remember, however, that you have it in your local files if you wanted to review it.\033[0m\n");
            printf("\033[94m\nCuriosity +10, Intelligence +10\033[0m\n");
            curiosity = curiosity + 10;
            intelligence = intelligence + 10;
            break;
        } else if (UserInput1 == 'N' || UserInput1 == 'n') {
            printf("\n\033[90mYou decide it might be best to get right into business. You remember, however, that you have it in your local files if you wanted to review it.\033[0m\n");
            printf("\033[94m\nCuriosity -10, Brave +10\n\033[0m");
            curiosity = curiosity - 10;
            brave = brave + 10;
            break;
        } else {
            printf("\nInvalid input! Please enter either Y or N.\n\n");
        }
    }

    enter();
    entranceHall();
    printf("You may now investigate the Pembroke Manor and its surroundings as you please!\nPlease use the map of the manor in your case file if you get lost, as you can only enter adjacent rooms!\nDepending on your choices and overall stats, new dialogue options or possible decisions can be made!\nMake sure to check the manor for new clues as you continue the story!\n");
    enter();
    printf("Finally, I will introduce the Action Meter! Every detective needs to have some sort of challenge.\nFor every dialogue option and action chosen from this point on, your Action Meter will go down! Entering rooms doesn't affect the meter.\nIf you are unable to solve the mystery of the Pembroke Manor before the Action Meter reaches 0, it's an automatic failure! Good Luck!!!\033[0m\n");
    enter();
    introFlag = 1; // Triggers the Action Meter to work
    printActionMeter();

    do {  //<--------------     Main Game Loop 
        roomChangeSelection();
    } while (actionMeter > 0);

    if (actionMeter <= 0 ){   // <------------ Game Over Failure
        printf("\n\nYou have run out of Action Meter and were unable to solve the mysteries of the Pembroke Family Manor. Game Over.");
    }
    return 0;
}