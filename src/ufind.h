/** @file
 * Header file for Union Find Data Structure
 * @author Gevorg Chobanyan
 * @date 11.04.2020
 */
#ifndef GAMMA_UFIND_H
#define GAMMA_UFIND_H
#include <stdbool.h>
#include <stdint.h>

/** @brief Structure storing a Union Find node
 */
typedef struct unode_t {
	struct unode_t* parent;  ///< parent of this node
	uint32_t player;         ///< player to which this node belongs
	uint16_t depth;          ///< depth for current node. 1 on creation
	bool visited;            ///< flag for visiting the current node
} unode_t;

/** @brief Returns a new unode_t
 * @param [in] player - to which player this unode belongs
 * @return new unode_t, NULL if no memory is available
 */
unode_t* new_unode(uint32_t player);

/** @brief Union find with path compression
 * Does nothing if @p element is NULL
 * @param [in] element - unode_t to perform find on
 * @return unode that was found
 */
unode_t* ufind(unode_t* element);

/** @brief Merge two unions
 * Does nothing if @p a or @p b is NULL
 * @param [in] a - first unode_t to join
 * @param [in] b - second unode_t to join
 * @return Value @p true if unode_ts were joined @p false,
 * if one of them is NULL or they are already joined
 */
bool ujoin(unode_t* a, unode_t* b);

#endif //GAMMA_UFIND_H
