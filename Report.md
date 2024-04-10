# Unsolved Problems
### Not able to use openChest() function for droploot from a boss or enemy
- The problem appears when I modify the chest in the function (taking items from the chest)
- After I modify it, the function closes and returns to the newGame() function, which is fine, but then the program crashes when I exit the else statement I started in.
- When I open the droploot but dont take anything and just leave, everything is fine
  
### When deleting bosses (maybe all enemies), wrong boss being deleted
- If I defeat boss1 and erase it, I am stil able to access boss1's name, hp, and coord
- When I go to that coord, nothing there
- When I am in battle with boss1, let the name be name1
- After deleting boss, I acess boss->getName(), but that returns name2
- This function should lead to undefined behavior in the first place, but it doesnt
- Currently using a system that checks for all bosses w/ hp = 0, and deleting all of those
- May switch to a system where I specifically delete the boss with an ID?

### openChest() function crashes when I change droploot (remove items)
- am not sure why it happens
- No problems happen when I open a regular chest (not enemy loot)
- May have to rewrite the way openChest() works

# Upcoming Changes
- Change how openChest works
- I want it so that the greatness of a chest depends on the enemy that drops it
- ex: a boss drops better loot than a minion
- Can make it so chest is generated inside function?
- Can make it so items are generated inside function?
- 

