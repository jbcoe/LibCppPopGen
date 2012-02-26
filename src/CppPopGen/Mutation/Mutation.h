#include "../CppPopGenBase.h"

BEGIN_CPP_POPGEN

class Mutation
{
	public:
	
	/// Get the location of the mutation represented as a double in [0,1]
	virtual double locus() const = 0;

	/// Get the simulation step in which the mutation was introduced
	virtual int arrivalTime() const = 0;

	/// Get the simulation step in which the mutation was fixed or lost
	/// it is an error to call this if the mutation is not fixed
	virtual int fixationTime() const = 0;

  /// Returns true if the mutation is fixed or lost
	/// (All organisms or no organisms carry the mutation)
  virtual bool isFixed() const = 0;

	/// Get Number of copies of the mutation in the population
	virtual int count() const = 0;

	/// Increase the count by one
	virtual int incrementCount() = 0;
	
	/// Decrease the count by one
	virtual int decrementCount() = 0;

	virtual ~Mutation() {}
};

END_CPP_POPGEN
