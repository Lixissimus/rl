#ifndef _RL_PLAN_PCRRTEXTENSIONS_H_
#define _RL_PLAN_PCRRTEXTENSIONS_H_

#include <boost/shared_ptr.hpp>
#include <boost/random.hpp>

#include <Eigen/Eigenvalues>

namespace rl
{
  namespace plan
  {
    class Gaussian {
    public:
      Gaussian(const ::rl::math::Matrix& particles)
      {
        this->init(particles);
      }

      Gaussian(const ::std::vector<::rl::math::Vector>& particles)
      {
        ::rl::math::Matrix p;
        p.resize(particles.size(), particles[0].size());
        for (int i = 0; i < particles.size(); ++i)
        {
          p.row(i) = particles[i];
        }
        this->init(p);
      }

      ::rl::math::Real mahalanobis(::rl::math::Vector& x)
      {
        return sqrt((x - this->mean).transpose() * this->covariance.inverse() * (x - this->mean));
      }

      ::rl::math::Matrix eigenvectors()
      {
        ::Eigen::EigenSolver<::rl::math::Matrix> eig(this->covariance);
        return eig.eigenvectors().real();
      }

      ::rl::math::Vector eigenvalues()
      {
        ::Eigen::EigenSolver<::rl::math::Matrix> eig(this->covariance);
        return eig.eigenvalues().real();
      }

      ::rl::math::Vector mean;
      ::rl::math::Matrix covariance;

    private:
      void init(const ::rl::math::Matrix& particles)
      {
        this->mean = particles.colwise().mean();
        if (particles.rows() == 1)
        {
          // just one particle
          this->covariance = ::rl::math::Matrix::Zero(particles.cols(), particles.cols());
          return;
        }
        // substract mean
        ::rl::math::Matrix centered = particles.rowwise() - this->mean.transpose();
        // calculate sample covariance
        this->covariance = centered.transpose() * centered / (particles.rows()-1);
      }
    };

    class GaussianState
    {
    public:
      GaussianState(const ::rl::math::Matrix& particles) :
      gaussianDistr(particles),
      gen(42),
      inCollision(false)
      {
        this->init();
      }

      GaussianState(const ::std::vector<::rl::math::Vector>& particles) :
      gaussianDistr(particles),
      gen(42),
      inCollision(false)
      {
        this->init();
      }

      void sample(::rl::math::Vector& q)
      {
        assert(q.size() == this->dims);

        for (int i = 0; i < this->dims; ++i)
        {
          q[i] = this->distributions[i](this->gen);
        }
      }

      Gaussian gaussian()
      {
        return this->gaussianDistr;
      }

      ::rl::math::Vector mean()
      {
        return this->gaussianDistr.mean;
      }

      ::rl::math::Matrix covariance()
      {
        return this->gaussianDistr.covariance;
      }

      void setCollision(const ::std::string& coll1, const ::std::string& coll2)
      {
        this->inCollision = true;
        this->collisionShape1 = coll1;
        this->collisionShape2 = coll2;
      }

      bool isInCollision()
      {
        return this->inCollision;
      }

      bool isSameCollision(const ::std::string& coll1, const ::std::string& coll2)
      {
        return (this->collisionShape1 == coll1 && this->collisionShape2 == coll2)
          || (this->collisionShape1 == coll2 && this->collisionShape2 == coll1);
      }
    private:
      void init()
      {
        this->dims = this->gaussianDistr.covariance.rows();
        for (int i = 0; i < this->dims; ++i)
        {
          ::rl::math::Real mean = this->gaussianDistr.mean[i];
          ::rl::math::Real std_dev = sqrt(this->gaussianDistr.covariance(i,i));
          distributions.push_back(boost::random::normal_distribution<>(mean, std_dev));
        }
      }

      Gaussian gaussianDistr;
      boost::random::mt19937 gen;
      ::std::vector<boost::random::normal_distribution<> > distributions;
      int dims;
      bool inCollision;
      ::std::string collisionShape1, collisionShape2;
    };
  }
}

#endif // _RL_PLAN_PCRRTEXTENSIONS_H_