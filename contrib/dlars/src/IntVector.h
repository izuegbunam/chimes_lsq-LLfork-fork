
class IntVector {
public:
	int *vec ;
	int dim ;

	IntVector(int d1)
		{
			dim = d1 ;
			
				vec = new int[d1] ;
		}
	IntVector(int d1, int val)
		{
			dim = d1 ;
			vec = new int[d1] ;
			for ( int j = 0 ; j < dim ; j++ ) {
				vec[j] = val ;
			}
		}
	IntVector()
		{
			dim = 0 ;
			vec = NULL ;
		}
	~IntVector()
		{
			
				delete[] vec ;
		}
	void realloc(int size) {
		// Reallocate the vector.
		delete [] vec ;
		vec = new int[size] ;
		dim = size ;
	}

	IntVector &operator=(const IntVector& in) {
		if ( dim !=in.dim ) {
			delete [] vec ;
			vec = new int [in.dim] ;
			dim = in.dim ;
		}
		for ( int j = 0 ; j < dim ; j++ ) {
			vec[j] = in.vec[j] ;
		}
		return *this ;
	}
		
	int size() const {
		return dim ;
	}
	void set(int i, int val) {
#ifdef DEBUG					
		if ( i >= dim ) {
			cout << "IntVector set out of bounds" << endl ;
			exit(1) ;
		}
#endif					
		vec[i] = val ;
	}
	void read(ifstream &file, int dim0) 
		{
			dim = dim0 ;
			vec = new int[dim] ;
			for ( int i = 0 ; i < dim ; i++ ) {
				int val ;
				file >> val ;
				set(i, val) ;
			}
		}
	int get(int idx) const {
#ifdef DEBUG					
		if ( idx >= dim ) {
			cout << "IntVector index out of bounds" << endl ;
			exit(1) ;
		}
#endif					
		return vec[idx] ;
	}
	void add(int idx, int val) {
		vec[idx] += val ;
	}

	void print() 
		{
			if ( RANK == 0 ) {
				cout << "[" << endl ;
				for ( int j = 0 ; j < dim ; j++ ) {
					cout << j << " " << vec[j] << endl ;
				}
				cout << "]" << endl ;
			}
		}

		void print(ofstream &of) 
		{
			if ( RANK == 0 ) {
				for ( int j = 0 ; j < dim ; j++ ) {
					of << j << " " << vec[j] << endl ;
				}
			}
		}
	
	void remove(int idx)
	// Remove the specified index from the vector.
		{
			if ( idx < 0 || idx >= dim ) {
				cout << "Error: bad index to remove from vector: " << idx << endl ;
			}
			for ( int i = idx ; i < dim - 1 ; i++ ) {
				vec[i] = vec[i+1] ;
			}
			--dim ;
		}

	void push(int val)
		// Add the value to the end of the vector.
	{
		int *newv = new int[dim+1] ;
		for ( int j = 0 ; j < dim ; j++ ) {
			newv[j] = vec[j] ;
		}
		newv[dim] = val ;
		delete [] vec ;
		vec = newv ;
		++dim ;
	}
	void add_mult(const IntVector &in, int factor)
	// Set out = out + factor * in
	{
		if ( in.dim != dim ) {
			cout << "Error in add_mult: dim mismatch\n" ;
			exit(1) ;
		}
		for ( int k = 0 ; k < dim ; k++ ) {
			vec[k] += factor * in.get(k) ;
		}
	}
	void clear()
	// Clear all entries of the vector.
	{
		if ( dim > 0 ) 
			delete [] vec ;
		vec = NULL ;
		dim = 0 ;
	}
} ;
