/**
 * @brief The Datastructures class
 * STUDENTS: Modify the code below to implement the functionality of the class.
 * Also remove comments from the parameter names when you implement an operation
 * (Commenting out parameter name prevents compiler from warning about unused
 * parameters on operations you haven't yet implemented.)
 */

#include "datastructures.hh"
#include "customtypes.hh"
#include <unordered_set>
#include <algorithm>

Datastructures::Datastructures()
{
}

Datastructures::~Datastructures()
{
  clear_all();
}

unsigned int Datastructures::get_bite_count()
{
    return bites.size();
}

void Datastructures::clear_all()
{
    bites.clear();
    biteIDs.clear();
    contours.clear();
    contourIDs.clear();
    bites_by_coord.clear();
    bites_by_name.clear();
    bites_by_distance.clear();
}

const std::vector<BiteID> Datastructures::all_bites()
{
    return biteIDs;
}

bool Datastructures::add_bite(BiteID id, const Name & name, Coord xy)
{
    auto it = bites.find(id);
    if (it != bites.end() || find_bite_with_coord(xy) != NO_BITE) {
        return false;
    }

    Distance distance_from_origin = abs(xy.x) + abs(xy.y);
    bites.emplace(id, Bite{id, name, xy, distance_from_origin});
    bites_by_coord.emplace(xy, id);
    bites_by_name.emplace(name, id);
    bites_by_distance.emplace(distance_from_origin, xy, id);
    biteIDs.push_back(id);
    return true;
}

Name Datastructures::get_bite_name(BiteID id)
{
    auto it = bites.find(id);
    return (it != bites.end()) ? it->second.name : NO_NAME;
}

Coord Datastructures::get_bite_coord(BiteID id)
{
    auto it = bites.find(id);
    return (it != bites.end()) ? it->second.xy : NO_COORD;
}

std::vector<BiteID> Datastructures::get_bites_alphabetically()
{
    std::vector<BiteID> sorted_bites;
    for (const auto& [name, id] : bites_by_name) {
        sorted_bites.push_back(id);
    }
    return sorted_bites;
}

std::vector<BiteID> Datastructures::get_bites_distance_increasing()
{
    std::vector<BiteID> sorted_bites;
    for (const auto& [distance, coord, id] : bites_by_distance) {
        sorted_bites.push_back(id);
    }
    return sorted_bites;
}


BiteID Datastructures::find_bite_with_coord(Coord xy)
{
    auto it = bites_by_coord.find(xy);
    return (it != bites_by_coord.end()) ? it->second : NO_BITE;
}

bool Datastructures::change_bite_coord(BiteID id, Coord newcoord)
{

    auto it = bites.find(id);
    if (it == bites.end() || find_bite_with_coord(newcoord) != NO_BITE) {
        return false;
    }

    Coord currentCoord = it->second.xy;
    Distance currentDistance = it->second.distance_from_origin;

    bites_by_coord.erase({currentCoord});
    bites_by_distance.erase({currentDistance, currentCoord, id});

    it->second.xy = newcoord;
    it->second.distance_from_origin = abs(newcoord.x) + abs(newcoord.y);

    bites_by_coord.emplace(newcoord, id);
    bites_by_distance.emplace(it->second.distance_from_origin, newcoord, id);

    return true;
}

bool Datastructures::add_contour(ContourID id, const Name &name, ContourHeight height, std::vector<Coord> coords)
{
    if (contours.find(id) != contours.end() || height > MAX_CONTOUR_HEIGHT || height < -MAX_CONTOUR_HEIGHT || coords.empty()) {
        return false;
    }

    contours.emplace(id, Contour{id, name, height, coords, NO_CONTOUR, {}, {}});
    contourIDs.push_back(id);
    return true;
}

std::vector<ContourID> Datastructures::all_contours()
{
    return contourIDs;
}

Name Datastructures::get_contour_name(ContourID id)
{
    auto it = contours.find(id);
    if( it != contours.end()) {
        return it->second.name;
    }
    return NO_NAME;
}

std::vector<Coord> Datastructures::get_contour_coords(ContourID id)
{
    auto it = contours.find(id);
    return (it != contours.end()) ? it->second.coords : std::vector<Coord>{NO_COORD};
}

ContourHeight Datastructures::get_contour_height(ContourID id)
{
    auto it = contours.find(id);
    return (it != contours.end()) ? it->second.height : NO_CONTOUR_HEIGHT;
}

bool Datastructures::add_subcontour_to_contour(ContourID id,
                                               ContourID parentid)
{
    auto it_sub = contours.find(id);
    auto it_parent = contours.find(parentid);
    if ( it_sub == contours.end() || it_parent == contours.end() ) {
        return false;
    }
    auto child_height = it_sub->second.height;
    auto parent_height = it_parent->second.height;
    if( it_sub->second.parent == parentid ||
        abs(child_height) < abs(parent_height) ||
        abs(child_height - parent_height) != 1) {
        return false;
    }
    it_sub->second.parent = parentid;
    it_parent->second.sub_contours.push_back(id);
    return true;
}

bool Datastructures::add_bite_to_contour(BiteID biteid, ContourID contourid)
{
    auto it_bite = bites.find(biteid);
    auto it_contour = contours.find(contourid);

    if (it_bite == bites.end() || it_contour == contours.end()) {
        return false;
    }
    const auto& coords = it_contour->second.coords;
    if (find(coords.begin(),coords.end(), it_bite->second.xy) == coords.end())
    {
        return false;
    }
    it_contour->second.bites.push_back(biteid);
    return true;
}

std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID id)
{
    auto it_bite = bites.find(id);
    std::vector<ContourID> contourIDs;

    if (it_bite == bites.end()) {
        contourIDs.push_back(NO_CONTOUR);
        return contourIDs;
    }

    for (const auto& [key, contour] : contours) {
        auto it = std::find(contour.bites.begin(), contour.bites.end(),id);
        if ( it != contour.bites.end()) {
            contourIDs.push_back(key);
            ContourID parentID = contour.parent;
            while (parentID != NO_CONTOUR) {
                if(contours.find(parentID) != contours.end()) {
                    contourIDs.push_back(parentID);
                    parentID = contours.at(parentID).parent;
                } else {
                    break;
                }
            }
        }
    }
    return contourIDs;
}

std::vector<ContourID> Datastructures::all_subcontours_of_contour(ContourID id)
{
    std::vector<ContourID> sub_childs;
    auto it = contours.find(id);

    if (it == contours.end()) {
        sub_childs.push_back(NO_CONTOUR);
        return sub_childs;
    }

    for (const auto& child :it->second.sub_contours) {
        sub_childs.push_back(child);

        std::vector<ContourID> child_sub_contours = all_subcontours_of_contour(child);
        sub_childs.insert(sub_childs.end(), child_sub_contours.begin(), child_sub_contours.end());
    }
    return sub_childs;
}

ContourID Datastructures::get_closest_common_ancestor_of_contours(ContourID id,
                                                        ContourID id2)
{
    auto it1 = contours.find(id);
    auto it2 = contours.find(id2);
    if (it1 == contours.end() || it2 == contours.end()) {
        return NO_CONTOUR;
    }

    std::unordered_set<ContourID> ancestors;

    id = contours[id].parent;
    while (id  != NO_CONTOUR) {
        ancestors.insert(id);
        id = contours[id].parent;
    }

    id2 = contours[id2].parent;
    while (id2  != NO_CONTOUR) {
        if(ancestors.find(id2) != ancestors.end()) {
            return id2;
        }
        id2 = contours[id2].parent;
    }
    return NO_CONTOUR;
}

bool Datastructures::remove_bite(BiteID id)
{
    auto it = bites.find(id);
    if (it == bites.end()) {
        return false;
    }

    Bite& bite = it->second;
    bites_by_coord.erase(bite.xy);
    bites_by_name.erase({bite.name, id});
    bites_by_distance.erase({bite.distance_from_origin, bite.xy, bite.id});
    biteIDs.erase(std::remove(biteIDs.begin(), biteIDs.end(), id), biteIDs.end());

    std::vector<ContourID> countour_to_be_removed = get_bite_in_contours(id);
    for (const ContourID contour : countour_to_be_removed) {
        auto contour_it = contours.find(contour);
        if (contour_it != contours.end()) {
            contour_it->second.bites.erase(std::remove(
                    biteIDs.begin(), biteIDs.end(), id), biteIDs.end());
        }
    }

    bites.erase(it);
    return true;
}

std::vector<BiteID> Datastructures::get_bites_closest_to(Coord xy)
{
    std::vector<BiteID> closest;
    std::vector<std::tuple<double, Coord, BiteID>> distances;

    auto manhattan_distance = [](Coord a, Coord b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    };

    for (const auto& bite : bites_by_distance) {
        const Coord& bite_coord = std::get<1>(bite);
        const BiteID& bite_id = std::get<2>(bite);

        double distance_to_xy = manhattan_distance(bite_coord, xy);

        distances.emplace_back(distance_to_xy, bite_coord, bite_id);
    }

    std::sort(distances.begin(), distances.end(),
        [xy, &manhattan_distance](const auto& a, const auto& b) {
          const Coord& coord_a = std::get<1>(a);
          const Coord& coord_b = std::get<1>(b);

          auto distance_a = manhattan_distance(coord_a, xy);
          auto distance_b = manhattan_distance(coord_b, xy);

          if (distance_a != distance_b) {
              return distance_a < distance_b;
          }

          if (coord_a.y != coord_b.y) {
              return coord_a.y < coord_b.y;
          }

          BiteID bite_id_a = std::get<2>(a);
          BiteID bite_id_b = std::get<2>(b);

          return bite_id_a < bite_id_b;
      });

    for (int i = 0; i < 3 && i < static_cast<int>(distances.size()); ++i) {
        closest.push_back(std::get<2>(distances[i]));
    }

    return closest;
}

