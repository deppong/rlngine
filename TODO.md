# TODO

# Software Architecture

I am seriously considering utilizing an ECS, however due to the complexity of the issue I kind of want 
to plan it out, as I can feel the scope creep lurking around the corner just thinking about it.

Each entity should be able to have an arbitrary amount of components


The main design issue is if I should have a list of entities that store their own components or have the manager contain
a list of all the specific components and make sure the index of all of them is maintained. Potential use of a hashmap is
very likely here

### Option 1:
The main problem here is that each component is not contiguous in memory, which would likely slow down the system
for processing each component quite a bit due to CPU cache misses.
```c++
    struct Component { 
        std::map<std::string, std::any> values;
    } component_t;

    struct entity {
            std::string id;
            std::vector<component_t> components;
    }entity_t;
            
```

### Option 2:
Here the problem is just a slight bit more code/complexity, however each component, (which a system will be accessing each one in a row) will be contiguous in memory, speeding up the game super fast!
```c++
    struct Component { 
        std::map<std::string, std::any> values;
    } component_t;

    struct entity_t {
        unsigned int id;
    };

    static const int MAX_ENTITIES = 4096;

    class EntityManager {
        public:
            entity_t addEntity();
            void addComponent(entity_t entity, int componentId);
            void destroy(entity_t entity);
        private:
            std::map<entity_t, int> entity_to_component;
            std::array<entity_t, MAX_ENTITIES> entities;
    };
``` 


### Here is a list of example components

| component name | behavior |
| --- | --- |
| stats | contains different stats (str,hp,dex, etc.) |
| transform | contains entity location, rotation, size |
| drawable | contains render information | 

### REMINDER!
In an ECS, Entities are just an ID, Components are just data,
and Systems are where the actual logic happens!

I am currently using std::any (c++17), to provide the developer to have 
components with multiple data types. There are other methods that I could
employ here, as this seems pretty naive.
Something like a template, or have something more complicated. In order to prevent
loads of typing `std::any_cast<type>(value)` I may use a component creator using
any of the following:

- json (cataclysm:dda uses)
- xml (caves of qud uses)
- csv?
- custom language (dwarf fortress uses)

Here is an example for the structure of a component
```c++
    template
    struct compnent_t{...}component_t;

    const int COLOR_BLUE = ((255<<24) + (200<<16) + (10<<8) + 20;

    component_t stats = {{
        {"STR", std::any_cast<int>(10)},
        {"CON", std::any_cast<int>(11)},
        {"DEX", std::any_cast<int>(14)},
        {"INT", std::any_cast<int>(14)}
    }};

    component_t transform = {{
        {"x",      std::any_cast<int>(20)},
        {"y",      std::any_cast<int>(30)},
        {"size",   std::any_cast<int>(15)},
        {"weight", std::any_cast<int>(10)}
    }};

    component_t drawable = {{
        {"tile_coord_x", std::any_cast<int>(5)},
        {"tile_coord_y", std::any_cast<int>(3)},
        {"color",   std::any_cast<int>(COLOR_BLUE)}
    }};
    
    component_t controllable = {{
        {"in_control", std::any_cast<bool>(true)}
    }};

    component_t description = {{
        {"name",        std::any_cast<std::string>("Kobold")},
        {"description", std::any_cast<std::string>("A small but devious creature.")}
    }};

```

### Example of the component manager layed out like json:
```json
// first std::map<string, map...>
// components
{
   "transform" : {
        // entity Id 0's transform component data:
        0 : {
            "x" : 10,
            "y" : 20
        },
        // entity Id 2's transform component data:
        2 : {
            "x" : 10,
            "y" : 20
        }
   },
   "drawable" : {
        0 : {
            "tile_coord_x" : 4,
            "tile_coord_y" : 10,
            "color" : COLOR_BLUE
        },
        2 : {
            "tile_coord_x" : 5,
            "tile_coord_y" : 3,
            "color" : COLOR_RED
        }
   },
   "stats" : {
        0 : {
            "STR" : 4,
            "CON" : 5,
            "DEX" : 2
        }
   }
}
```

### So now we have the data
Next should be the systems, and arguably the most simple one to implement 
would be the drawable system, as I already have most of that code in place
to begin with. One more object that might need to be modeled would be the 
world, which will handle all of the calls from the entity manager, systems 
and components.

For the Drawable system I expect 2 components, the transform, and the 
drawable component

```c++
    component_t transform = EntityManager.components.find("transform");
    if (transform == EntityManager.components.end())

```
