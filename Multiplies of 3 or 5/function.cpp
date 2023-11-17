int solution(int number)
{
    // Initializing sum with default value
    int sum = 0;

    // For all natural numbers less than a given number
    for (int count = 1; count < number; count++)
    {
        if (count % 3 == 0 || count % 5 == 0)
        {
            // The result of this program is the return of the sum
            // of all natural numbers that are divisible by 3 or 5
            sum += count;
        }
    }

    return sum;
}
