#ifndef _SYSCALL
#define _SYSCALL

//Démarre l'application numéro 'appno' (commence à 0)
//P1, P2 et P4 doivent toujours etre à 0;
//Ne fonctionne pas sur l'émulateur
int StartAnyApp(int P1, int P2, int appno, int P4);

//Ajoute une touche dans le buffer de touches
//Exemple, si vous ajoutez KEY_CTRL_EXE, le prochain GetKey(int*) se comportera comme si
//l'utilisateur avait appuyé sur EXE
//Je ne sais pas a quoi sert 'mode, ça marche avec 0
void KBD_PutKey(unsigned int keycode, int mode);

//Scan les addin de la mémoire de stockage
//Exemple, si votre addin copie un .G1A dans la mémoire de stockage (depuis la carte SD par exemple)
//il faut appeler Register_addin() avant de pouvoir lancer ce .G1A avec StartAnyApp()
void Register_Addin();

//Retourne l'adresse de la VRAM, quelque soit l'OS (fonctionne aussi sur l'émulateur)
char* VRam_Base();


/***********************************************************************/
/** Les 3 syscalls suivants servent a acceder à la mémoire principale **/
/** Je n'ai pas beaucoup d'informations,                              **/
/** je ne vous conseil pas de les utiliser avant d'en savoir plus.    **/
/***********************************************************************/

//Cherche un élément dans un dossier de la mémoire principale.
//Exemple: "system" pour les programmes BASIC, "@REV2" pour les pictures
int MCS_SearchDirectoryItem(unsigned char* dir, unsigned char* item, char* flags_0, void* item_ptr, int* data_ptr, int* data_length);

//Crée un fichier dans un dossier de la mémoire principale et écrit dedans.
//dirtype=1 pour le dossier "system", c'est le vrai nom du dossier des programmes BASIC
int MCS_PutInternalItem(char dirtype, unsigned char* item, int data_len, void* buffer);

//Supprime un élément d'un dossier de la mémoire principale
int MCS_DeleteInternalItem(char dirtype, unsigned char* item);


/******************************************************************/
/** TOUS les syscalls suivants sont tirés de fxreverse-doc-1.pdf **/
/******************************************************************/

//Défini la position du curseur, équivalent à locate(int, int) de fxlib.h
//Retourne 1 si ça a marché, 0 si les coordonnées sont en dehors de l'écran
int Cursor_SetPosition(char column, char row);

//Défini le style du curser (0=normal, 1=SHIFT, 2=ALPHA)
//Retourne 1 si ça a marché, 0 si l'argument n'est pas bon
int Cursor_SetFlashStyle(short int flashstyle);

//Défini le mode de clignottement du curseur. Si flashmode!=0, le curseur clignotte, si flashmode==0, le curseur ne clignotte plus
void Cursor_SetFlashMode(long flashmode);

//Permet de récupérer des infos sur le style du curseur
//settingsarray contient dans cet order : colonne, ligne, flash style, fhash mode (il faut donc un tableau de 4 int)
//Retourne : on n'en sait rien
unsigned int Cursor_GetSettings(unsigned int settingsarray[]);

//Equivalent de Cursor_SetFlashMode(0);
void Cursor_SetFlashOff();


/*************************************************************************/
/** Les syscalls suivants servent a appeler les applications du système **/
/*************************************************************************/

//Les arguments sont les mêmes que pour AddIn_main, si runMode vaut 0, c'est qu'on appelle l'application depuis une e-activity
//Dans ce cas, stripNum donne le numéro du strip de l'e-activity
//Pour exécuter normalement une application, mettez runMode à 1
void App_CONICS(int runMode, unsigned short stripNum);
void App_DYNA(int runMode, unsigned short stripNum);
void App_EACT(int runMode, unsigned short stripNum);
void App_EQUA(int runMode, unsigned short stripNum);
void App_PRGM(int runMode, unsigned short stripNum);
void App_FINANCE(int runMode, unsigned short stripNum);
void App_GRAPH(int runMode, unsigned short stripNum);
void App_LINK(int runMode, unsigned short stripNum);
void App_MEMORY(int runMode, unsigned short stripNum);
void App_RECUR(int runMode, unsigned short stripNum);
void App_RUNMAT(int runMode, unsigned short stripNum);
void App_STAT(int runMode, unsigned short stripNum);
void App_SYSTEM(int runMode, unsigned short stripNum);


/**********************************************************/
/** Les syscall suivants servent à l'acces au port série **/
/** Le buffer de réception fait 1ko,                     **/
/** et le buffer d'envoi fait 256 octets.                **/
/**********************************************************/

//Lit un caractère du buffer de réception et le copie a l'adresse pointée par 'dest'
//Retourne 0 en cas de succes, 1 si le buffer est vide, 3 si la connexion n'est pas établie
int Serial_ReadByte(unsigned char *dest);

//Lit 'max' octets du buffer de réception et les écrit dans 'dest'
//'size' donne le nombre d'octets lu
//Retourne 0 en cas de succes, 1 si le buffer est vide, 3 si la connexion n'est pas établie
int Serial_ReadBytes(unsigned char *dest, int max, short *size);

//Ecrit 'byte' dans le buffer d'envoi
//Retourne 0
int Serial_WriteByte(unsigned char byte);

//Ecrit 'size' octets dans le buffer d'envoi depuis l'adresse 'scr'
//Retourne 0 en cas de succes, 2 si le buffer est trop plein, 3 si la connexion n'est pas établie
int Serial_WriteBytes(unsigned char *src, int size);

//FIFO = first in first out
int Serial_WriteByteFIFO(unsigned char byte);

//Retourne la taille des données du buffer de réception
int Serial_GetRxBufferSize(void);

//Retourne l'espace disponible dans le buffer d'envoi
int Serial_GetTxBufferFreeCapacity(void);

//Vide le buffer de réception
//Retourne 0 en cas de succes, 3 si la connexion n'est pas établie
int Serial_ClearReceiveBuffer(void);

//Vide le buffer d'envoi
//Retourne 0
int Serial_ClearTransmitBuffer(void);

//Ouvre et prépare l'interface de communication
//Pour plus de détails, consulter fxreverse-doc-1.pdf ci joint
int Serial_Open(unsigned char *conf);

//Ferme l'interface de communication et vide les buffers d'envoi et de réception
//Si 'mode'==1, la communication est coupée sans regarder s'il reste des données a transmettre
//Si 'mode'!=1, la fonction ne ferme pas l'interface de communication s'il reste des données a transmettre
//et retourne 5
//Retourne 0 en cas de succes (communication terminée) et 5 s'il reste des données a transmettre
int Serial_Close(int mode);

//Copie l'octet numéro 'index' du buffer de réception vers 'dest' si 'index' ne dépasse pas les données du buffer
//Retourne 0 en cas de succes, 1 si 'index' dépasse les données du buffer, 3 si la communication n'est pas établie
int Serial_Peek(int index, unsigned char *dest);

//Récupère le statut de la connexion
//Retourne 1 si la connexion est établie, 3 sinon
int Serial_IsOpen(void);

/*********************************************************************/
/** Les syscalls suivants servent a l'acces aux variables Setup     **/
/** Il est précisé dans la doc que ces syscall sont valides         **/
/** pour l'OS 1.2, mais peut etre pas pour les versions supérieures **/
/*********************************************************************/

//Lit la variable Setup numéro 'index'
//Retourne la valeur de la variables Setup numéro 'index'
char Setup_GetEntry(unsigned int index);

//Ecrit la valeur 'value' dans la variables Setup numéro 'index'
//Retourne l'adresse du tableau des variables Setup
char *Setup_SetEntry(unsigned int index, char value);

//Retourne l'adresse de la variable Setup numéro 'index'
char *Setup_GetEntryPtr(unsigned int index);

/*************************************************************************/
/** Les syscalls suivants servent a acceder aux variables               **/
/** utilisées par les programmes BASIC, A-Z, r, theta et Ans.           **/
/** Les variables A-Z sont représentées par leur code ASCII (0x41-0x5A) **/
/** r, thete et Ans sont représentées par les codes 0xCE, 0xCD et 0xC0  **/
/*************************************************************************/

//Lit la variable 'variable' et copie sa valeur dans 'dest'
//'dest' doit etre un tableau de 24 octets
//Retourne le pointeur envoyé, 'dest'
char *Alpha_GetData(char variable, char *dest);

//Ecrit le contenu de 'scr' dans la variable 'variable'
//'scr doit etre un tableau de 24 octets
//Si 'variable' est valide, retourne 0, sinon retourne 'variable'
char Alpha_SetData(char variable, char *src);

//Initialise toutes les variables Alpha, excepté Ans
void Alpha_ClearAll(void);

int RTC_GetTicks(void);

#endif
