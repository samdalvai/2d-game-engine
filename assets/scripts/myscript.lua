-- This is a Lua variable
some_variable = 9 * 6

-- Lua table with values for initialization of Game
config = {
    title = "My table",
    fullScreen = true,
    resolution = {
        width = 800,
        height = 600
    }
}

function factorial_tail_recursive(n)
    if n == 0 then
        return 1
    else
        return n * factorial_tail_recursive(n - 1)
    end
end

-- Example usage
local number = 5
local result = factorial_tail_recursive(number)
print("The factorial of " .. number .. " is " .. result)

function factorial_loop(n)
    factorial = 1
    current = n
    while current > 0 do
        factorial = result * current
        current = current -1
    end

    return factorial
end

-- Example usage
local number = 5
result = factorial_loop(number)
print("The factorial of " .. number .. " is " .. result)