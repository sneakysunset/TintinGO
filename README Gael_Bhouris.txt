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
