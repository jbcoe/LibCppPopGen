class Mutation
{
	private:
		double m_selectiveAdvantage;
		size_t m_count;
		size_t m_arrivalTime;
		size_t m_fixationTime;
		std::string m_name;

	public:

		Mutation(const std::string& name, size_t arrivalTime, double selectiveAdvantage):
			m_selectiveAdvantage(selectiveAdvantage),
			m_count(0),
			m_arrivalTime(arrivalTime), 
			m_fixationTime(-1),
			m_name(name)
	{
	}

		const std::string& name() const
		{
			return m_name;
		}

		double selectiveAdvantage() const
		{
			return m_selectiveAdvantage;
		}

		int arrivalTime() const
		{
			return m_arrivalTime;
		}

		int fixationTime() const
		{
			return m_fixationTime;
		}

		bool isFixed() const
		{                       
			return (m_fixationTime != -1);
		}

		void setFixed(int fixationTime)
		{
			m_fixationTime = fixationTime;
		}

		int count() const
		{
			return m_count;
		}

		void incrementCount()
		{
			++m_count;
		}

		void decrementCount()
		{
			--m_count;
		}

		~Mutation() {}
};
