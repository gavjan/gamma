/** @file
 * Header file for Union Find Data Structure
 * @author Gevorg Chobanyan
 * @date 11.04.2020
 */

#ifndef GAMMA_UFIND_H
#define GAMMA_UFIND_H

#include <stdbool.h>
#include <stdint.h>

/** @brief typedef for unode_t in order to hide it
 */
typedef struct unode unode_t;

/** @brief macro for no winner
 */
#define NO_WINNER 0

/** @brief macro for uint128_t
 */
typedef unsigned __int128 uint128_t;

/** @brief enum for directions
 */
enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

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

/** @brief Set unode's parent
 * @param [in] element - Pointer to unode to be changed
 * @param [in] parent - parent to be set
 */
void set_parent(unode_t* element, unode_t* parent);

/** @brief Set unode's depth
 * @param [in] element - Pointer to unode to be changed
 * @param [in] depth -  depth to be set
 */
void set_depth(unode_t* element, uint16_t depth);

/** @brief Set unode's visited flag
 * @param [in] element - Pointer to unode to be changed
 * @param [in] visited - visited flag to be set
 */
void set_visited(unode_t* element, bool visited);

/** @brief Get unode's player
 * @param [in] element - Pointer to unode to be changed
 * @return player of unode
 */
uint32_t get_player(unode_t* element);

/** @brief Get unode's visited flag state
 * @param [in] element - Pointer to unode to be changed
 * @return visited flag of unode
 */
bool get_visited(unode_t* element);

#endif /* GAMMA_UFIND_H */
