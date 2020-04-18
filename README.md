A fixed box with name 'id' is defined like this:

    +-[id]--+
    |       |
    | Fixed |
    |       |
    +-------+

A box that is variably sized:

    +-[id]-~+  ;; width
    |       |
    | VaryW |
    |       |
    +------~+

    +-[id]--+
    |       |
    | VaryH |
    :       :  ;; height
    +-------+

    +-[id]-~+  ;; width
    |       |
    | Vary  |
    :       :  ;; height
    +------~+

A box can be told to stick left, right, up, or down:

    ^-[id]-^   ^-[id]-^   ^-[id]-^
    |  U&L |   |  Up  |   |  U&R |
    <------+   +------+   +------>

    <-[id]-+              +-[id]->
    |  L   |              |  R   |
    <------+              +------>

    <-[id]-+   +-[id]-+   +-[id]->
    |  U&L |   |  Up  |   |  U&R |
    v------v   v------v   v------v

    ^-[id]->
    |  All |    ;; stick in every direction
    <------v

We can build a box that expands to fill its container:

    ^~--[id]--~>
    |          |
    :    All   :
    |          |
    <~--------~v

Boxes are not allowed to overlap when there is a direct sibling relationship. The size of
the boxes are ratios as specified by column & row count in the directive.

Example UI:

    ^-[main]-------------------~>
    :^-[listing]-~>^-[state]--~>:
    |:            ::           :|
    ||            ||           ||
    ||            ||           ||
    ||            ||           ||
    |<------------v<----------~v|
    |<-[entry]----------------~>|
    ||                         ||
    |v------------------------~v|
    <--------------------------~v

Parsing the box is a bit of a pain, but the nice part is that there's no "overlapping" of
siblings. That means we can use a simple grid to represent the initial description of
the boxes. Furthermore, we can use the "ID" to allow secondary styling of the boxes.
Constraint layout is simplified because there's no shenanigans possible with sibling
layout.

The only real issue with this system (as with many declarative systems like it), is that
it's hard to describe "dynamic" UIs. For instance, let's say we wanted to describe a
table (spreadsheet) with removable/addable columns/rows. As another example: there's no
way to describe a drop down list *in line*.

About the best I can imagine for dynamic elements is to extend the `~` and `:` metaphor:

    ;; dynamic set of elements, all named '0'
    +-[0]-+  ~  +-[0]-+ ;; '~' means 'duplicate horizontally'
    |     |     |     |
    +-----+     +-----+
    :                 : ;; ':' means 'duplicate vertically'
    +-[0]-+     +-[0]-+
    |     |     |     |
    +-----+  ~  +-----+

Related to this concept is the notion that the user should be able to resize a UI element:

    +-[I]-/+ ;; horizontally resizable
    |      |
    /      / ;; vertically   resizable
    +-----/+

Things the declarative language explicitly does *not* do:
1. Describe actions, e.g., clicking, dragging, scrolling, panning, etc.
2. Describe styling, e.g., border thickness, padding, margin, color, etc.
3. Describe content, e.g., text, images, etc.
