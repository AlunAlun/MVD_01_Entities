### La Salle - Universitat Ramon Llull : Master in Advanced Videogame Development
## Engine Programming - 01-Entities

### TODO

#### in Components.h
 - fill in MeshComponent properties

#### in GraphicsSystem.cpp
 - move all GL and rendering code from Game 

#### in Game.cpp
 - call init and update functions of GraphicSystem
 - create entity for plane - use function defined in ECS
 - create mesh component for plane - use function in ECS
 - assign mesh component vao and num tris from created plane geometry

 - change position of plane using transform component:
   ECS.getComponentFromEntity<Transform>(entity_id).translate(0.0f, 1.0f, 3.0f);

 - Advanced: create a second entity and new Mesh Component
   which uses the same geometry
 - draw both entities in different positions				
