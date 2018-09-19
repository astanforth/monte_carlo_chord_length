// The values I get are slightly under what they should be. This can be seen once you run
// the program. No solution found yet. With millions of trials, it should be correct to
// around 3 places at least.

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// Function to generate a random number in the range of [min, max).
double double_rand(double min, double max)
{
	double f = (double)rand() / (RAND_MAX + 1);
	return min + f * (max - min);
}

int main()
{
    int num_trials = 100000000;

    int i, j; // index variables
	double pi = 3.14159265358979323846;

  // The initial radius, the change in radius with each loop, and how many different radii to test.
	double radius = 0.5;
	double radius_increment = 0.5;
	int radius_steps = 10;

	double dist;
	double chord_length, chord_length_sum;

	double x0, x1, y0, y1, z0, z1, phi, theta;

	double* dist_array = new double[num_trials];
	// An array to save the values of each distance to compute the standard deviation.
	double std_dev;

	// Loop through each radius. 
	for(j = 0; j < radius_steps; j++)
    {
        // Initialize values to 0.
        std_dev = 0;
        chord_length_sum = 0;

	// Update the radius. 
        radius = radius + radius_increment;

        for(i = 0; i < num_trials; i++)
        {
            // Generate the first point on the sphere.
            theta = double_rand(0, pi);
            phi = double_rand(0, 2*pi);

            x0 = radius * sin(theta) * cos(phi);
            y0 = radius * sin(theta) * sin(phi);
            z0 = radius * cos(theta);

            // Generate the second point on the sphere.
            theta = double_rand(0, pi);
            phi = double_rand(0, 2*pi);

            x1 = radius * sin(theta) * cos(phi);
            y1 = radius * sin(theta) * sin(phi);
            z1 = radius * cos(theta);

            // Calculate the distance between the two points using the distance formula.
            dist = sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0) + (z1-z0)*(z1-z0));

            // Save all the data for standard deviation calculations.
            dist_array[i] = dist;

            chord_length_sum = chord_length_sum + dist;
        }

        // Compute the average.
        chord_length = chord_length_sum / (num_trials);

        // Compute the standard deviation.
        for(i = 0; i < num_trials; i++)
        {
            std_dev = std_dev + (dist_array[i] - chord_length)*(dist_array[i] - chord_length);
        }

        std_dev = sqrt(std_dev/num_trials);

        cout << "radius = " << radius << endl;
        // The answer should be 4r/3, so output to see how far off from the answer I am.
        cout << "4r/3 = " << 4*radius/3.0 << endl;  
        cout << chord_length << endl;
        cout << "sigma = " << std_dev << endl;
    }

    return 0;
}
