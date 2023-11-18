public static string Likes(string[] name)
{
    // Inititalizing length of the "name" array
    // for using it in return-switch statement
    int length = name.Length;

    // Return-switch statement
    return length switch
    {
        // numbers are the cases
        0 => "no one likes this",
        1 => $"{name[0]} likes this",
        2 => $"{name[0]} and {name[1]} like this",
        3 => $"{name[0]}, {name[1]} and {name[2]} like this",
        // Symbol "_" is default case
        _ => $"{name[0]}, {name[1]} and {length - 2} others like this",
    };
}
