#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_

#include <cstring>
#include <utility>

namespace qh
{
    template<class T>
    class vector {
    public:
        //ctor
        vector()
            : data_(NULL), size_(0), rsize_(4)
        {
			data_ = new T[rsize_];
        }

        explicit vector( size_t n, const T& value = T())
        {
			rsize_ = n << 2;
            data_ = new T[rsize_];
            for (size_t i = 0; i < n; i++)
            {
                data_[0] = value;
            }
			size_ = n;		// assignment after successfully new to provide exception safe
        }


		// copy ctor
		vector(const vector<T> &other) {
			data_ = new T[other.rsize_];

			for (size_t i = 0; i < data_;++i)
				data_[i] = other.data_[i];
			size_ = other.size_;
			rsize_ = other.rsize_;
		}

        vector<T>& operator=(const vector<T>& rhs)
        {
			// copy and swap
			vector<T> tvec = vector<T>(rhs);
			swap(tvec);
			return *this;
        }

        //dtor
        ~vector()
        {
            if (data_)
            {
                delete [] data_;
            }
        }

        //get
        size_t size() const
        {
            return size_;
        }

        // set & get
        T& operator[](size_t index);

        // set
        void push_back(const T& element);
        void pop_back();
        void resize(size_t sz);
        void reserve();
        void clear();
        bool empty();

		// swap
		void swap(vector<T> &rhs) {
			using std::swap;
			swap(size_, rhs.size_);
			swap(rsize_, rhs.rsize_);
			swap(data_, rhs.data_);
		}

    private:
        T*      data_;
        size_t  size_;
		size_t  rsize_;

		inline void reallocate(size_t i);
    };

	/**
	 * This function reallocate size and
	 * copy the original data to new room
	 */
	template <typename T>
	inline void vector<T>::reallocate(size_t i) {
		T *tdata = new T[i];
		memcpy(tarr, data_, size_ * sizeof(T));
		delete [] data_;
		data_ = tdata;
		rsize_ = i;
	}

	/**
	 * Access the element according to the <code>index</code>
	 *
	 * @note operator[] don't check the validation of <code>index</code>
	 *
	 * @param index - index to access
	 */
	T& operator[](size_t index) {
		return data_[index];
	}


	/*
	 * Push a element at the back of vector
	 *
	 * @param element - the value to push back
	 */
	template<typename T>
	void vector<T>::push_back(const T& element) {
		if (size_ == rsize_) {
			reallocate((rsize_ << 1));
		}
		data_[size_++] = element;
	}

	/**
	 * Pop a element from the back of vector
	 */
	template<typename T>
	void vector<T>::pop_back() {
		--size_;
		data[size_].~T();
	}

	/**
	 * Resize the vector size
	 *
	 * @param sz - the size to set
	 */
	template<typename T>
	void vector<T>::resize(size_t sz) {
		if (sz > rsize_) {
			reallocate(i);
			rsize_ = i;
		} else if (sz < size_) {
			for (size_t i = sz; i < size_; ++i)
				data_[i].~T();
		}
		size_ = sz;
	}

	/**
	 * Reverse the vector
	 */
	template<typename T>
	void vector<T>::reverse() {
		using std::swap;
		size_t left = 0, right = size_ - 1;

		while (left < right)
			swap(data_[left++], data_[right--]);
	}

	/**
	 * Remove all elements
	 */
	template<typename T>
	void vector<T>::clear() {
		for (size_t i = 0; i < size_; ++i)
			data_[i].~T();
	}

	/**
	 * Check if the vector has no elements
	 *
	 * @return return <code>true</code> if empty otherwise <code>false</code>
	 */
	template<typename T>
	bool vector<T>::empty() {
		return size_ == 0;
	}
}

#endif

