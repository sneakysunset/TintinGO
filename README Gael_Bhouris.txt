Managers :
- AMainGameMode : Game Mode et Game Manager, gestion des tiles et des états.
- AGridManager : Gestion des tiles en éditeur.
- AClickInputManager : Pawn possédant le characterController.
- AClickInputManagerController : CharacterController gérant les inputs.
- UCoreUI : Classe des widgets dans la scène.
- AGlobalGameManager : Game Instance, Finalement je n'ai rien mis dedant.
- AMyGameStateBase : GameState, Finalement je n'ai rien mis dedant.

Actors :
- ATile : Classe des tiles dans la scène s'occupe aussi de l'instantiation des ATileActor dans la scène.
- ATileActor : Classe de base dont héritent tous les objets se placeant sur une tile.
- ATileActor_Character : Classe héritant de ATileActor dont héritent tous les objets se déplacant de tile en tile

States :
- UState : State de base dont tous les autres State héritent.
- UState_TActor : State de base pour tous les States se déroulant au niveau d'abstraction inférieur (pour un acteur seulement et géré par une barrière).
- UBarrier : Classe de transition s'occupant de l'initialisation et des processus des UState_TActors.


Information sur le développement :

Vous trouverez tous nos scripts dans le fichier source sans être rangé dans des sous-folder. 
Nous avons malheuresement compris qu'on pouvait ranger les scripts trop tard et réarranger tous les include paths auraient pris trop de temps. C'est donc assez dure à naviguer.

Nous avions commencé sur une structure basé autour de deux Managers le grid manager et le game manager en singleton.
Nous avons plus tard fais face à des nombreux problèmes de packaging à cause de la structure en singleton et avons donc décidé de rassembler les deux scripts dans le Game Mode à part les fonctions éditors que nous avons gardé dans le GridManager. Le game mode (MainGameMode) est donc composé de nombreuses fonctions et fields.

Nous détestons avec passion Unreal Engine! Mais malgrès ca nous avons travaillé avec hargne pour essayer de faire un projet fonctionnel, souvent au prix de code peu propre surtout en fin de projet. En conséquence certains gameplay element que nous avons designé de manière extensible ont finis par être remplacé par des valeurs hard codées. Je pense notemment au nombre d'indice qui est limité à deux dans le projet et au condor.

J'espère malgrés cela que notre code ne sera pas trop dure à lire et que vous arriverez à vous y retrouver.
Bonnes fêtes!