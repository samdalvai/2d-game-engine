-- This is a Lua variable
some_variable = 9 * 6
user_name = "Samuel"

print("Name is: "..user_name)
print("This is the value in Lua: "..some_variable)

if some_variable == 42 then
    print("The variable is 42")
end

-- Lua table with values for initialization of Game
config = {
    title = "My table",
    fullScreen = true,
    resolution = {
        width = 800,
        height = 600
    }
}