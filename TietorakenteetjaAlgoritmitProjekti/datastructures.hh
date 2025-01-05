// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include "customtypes.hh"
#include <utility>
#include <vector>
#include <unordered_map>
#include <set>

template <typename Type>
Type random_in_range(Type start, Type end);

struct Bite{
    BiteID id;
    const Name name;
    Coord xy;
    Distance distance_from_origin;
};

struct Contour {
    ContourID id;
    const Name name;
    ContourHeight height;
    std::vector<Coord> coords;
    ContourID parent;
    std::vector<ContourID> sub_contours;
    std::vector<BiteID> bites;
};

class Datastructures
{
public:
  Datastructures();
  ~Datastructures();

  // Estimate of performance: O(1)
  // Short rationale for estimate: Does one command
  unsigned int get_bite_count();

  // Estimate of performance: O(n)
  // Short rationale for estimate: Cleanes vectors and the number of n
  // affects it.
  void clear_all();

  // Estimate of performance: O(n)
  // Short rationale for estimate: Shows all bites so the number of n
  // affects it.
  const std::vector<BiteID> all_bites();

  // Estimate of performance: O(n)
  // Short rationale for estimate: One for loop so the number of n
  // affects it.
  bool add_bite(BiteID id, const Name & name, Coord xy);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Uses find and affects with number
  // of embryos.
  Name get_bite_name(BiteID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Uses find and affects with number
  // of embryos.
  Coord get_bite_coord(BiteID id);

  // We recommend you implement the operations below only after implementing the
  // ones above

  // Estimate of performance: = O(nlogn)
  // Short rationale for estimate: the sort function makes it that it goes
  // logaritmic
  std::vector<BiteID> get_bites_alphabetically();

  // Estimate of performance: O(nlogn)
  // Short rationale for estimate: the sort function makes it that it goes
  // logaritmic
  std::vector<BiteID> get_bites_distance_increasing();

  // Estimate of performance: O(n)
  // Short rationale for estimate: The loop affects with number
  // of embryos.
  BiteID find_bite_with_coord(Coord xy);

  // Estimate of performance: O(n)
  // Short rationale for estimate: The loop affects with number
  // of embryos.
  bool change_bite_coord(BiteID id, Coord newcoord);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Uses find and affects with number
  // of embryos.
  bool add_contour(ContourID id, const Name & name, ContourHeight height,
                   std::vector<Coord> coords);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Shows all bites so the number of n
  // affects it.
  std::vector<ContourID> all_contours();

  // Estimate of performance: O(n)
  // Short rationale for estimate: Uses find and affects with number
  // of embryos.
  Name get_contour_name(ContourID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Uses find and affects with number
  // of embryos.
  std::vector<Coord> get_contour_coords(ContourID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Uses find and affects with number
  // of embryos.
  ContourHeight get_contour_height(ContourID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Uses find and affects with number
  // of embryos.
  bool add_subcontour_to_contour(ContourID id, ContourID parentid);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Uses find and affects with number
  // of embryos.
  bool add_bite_to_contour(BiteID biteid, ContourID parentid);

  // Estimate of performance: O(n^2)
  // Short rationale for estimate: Checks contour and it's children
  // for loop and while loop.
  std::vector<ContourID> get_bite_in_contours(BiteID id);

  // Non-compulsory operations

  // Estimate of performance: O(n)
  // Short rationale for estimate: Depends heavily on how much
  // you use subcontours
  std::vector<ContourID> all_subcontours_of_contour(ContourID id);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<BiteID> get_bites_closest_to(Coord xy);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Deletes umbreons so depends
  // on the count of them
  bool remove_bite(BiteID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Depends heavily on how much
  // you use subcontours
  ContourID get_closest_common_ancestor_of_contours(ContourID id1,
                                                    ContourID id2);

private:
  std::unordered_map<BiteID, Bite> bites;
  std::unordered_map<Coord, BiteID> bites_by_coord;
  std::set<std::pair<Name,BiteID>> bites_by_name;
  std::set<std::tuple<Distance, Coord, BiteID>> bites_by_distance;
  std::vector<BiteID> biteIDs;
  std::unordered_map<ContourID, Contour> contours;
  std::vector<ContourID> contourIDs;
};

#endif // DATASTRUCTURES_HH
